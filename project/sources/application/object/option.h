//*****************************************************************************
//
// option
//
// Author		: Ryotaro Arai
//
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _OPTION_H_
#define _OPTION_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"
#include "system/direct_input/direct_input.h"
#include "option/option_data.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class OptionBg;
class KeyConfigOk;
class KeyConfigCancel;
class KeyConfigSpecial;
class KeyConfigPause;
class KeyConfigJump;
class OptionLogo;
class VolumeLogo;
class KeyconfigLogo;
class BgmVolume;
class SeVolume;

//*****************************************************************************
// class definition
//*****************************************************************************
class Option : public Basic
{
public:
	enum OPTION_SCENE
	{
		OPTION_MIN = -1,
		OPTION_VOLUME_BGM = 0,
		OPTION_VOLUME_SE,
		OPTION_KEY_CONFIG_OK,
		OPTION_KEY_CONFIG_CANCEL,
		OPTION_KEY_CONFIG_SPECIAL,
		OPTION_KEY_CONFIG_PAUSE,
		OPTION_MAX
	};

	static const D3DXVECTOR2 DEFAULT_MENU_SIZE;
	static const D3DXVECTOR2 EXPAND_MENU_SIZE;

	// constructor
	Option(void);

	// destructor
	virtual ~Option(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// 
	void Exchange(INPUT_EVENT* out_input_event,INPUT_EVENT input_event);

	void Load(void);

	void __is_indication(const bool indication){ is_indication_ = indication;}
	const bool __is_indication(void)const{ return is_indication_;}

private:
	static const f32 VOLUME_MIN;
	static const f32 VOLUME_MAX;
	static const f32 VOLUME_RATE;

	OptionBg* option_bg_;
	KeyConfigOk* key_config_ok_;
	KeyConfigCancel* key_config_cancel_;
	KeyConfigSpecial* key_config_special_;
	KeyConfigPause* key_config_pause_;
	KeyConfigJump* key_config_jump_;
	OptionLogo* option_logo_;
	VolumeLogo* volume_logo_;
	KeyconfigLogo* keyconfig_logo_;
	BgmVolume* bgm_volume_;
	SeVolume* se_volume_;

	s32 cursor_x_;
	s32 cursor_y_;
	bool is_indication_;
	bool is_select_;
	KEY_CODE is_exchange_;

	OPTION_DATA option_data_;

	//KEY_CONFIG key_config_temp_[5];
	s32 bgm_size_temp_;
	s32 se_size_temp_;
};

#endif	// _OPTION_H_

//---------------------------------- EOF --------------------------------------

