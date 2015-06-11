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
	static const D3DXVECTOR2 DEFAULT_MENU_SIZE;
	static const D3DXVECTOR2 EXPAND_MENU_SIZE;
	enum OPTION_SCENE
	{
		OPTION_MIN = -1,
		OPTION_VOLUME_BGM = 0,
		OPTION_VOLUME_SE,
		OPTION_KEY_CONFIG_OK,
		OPTION_KEY_CONFIG_CANCEL,
		OPTION_KEY_CONFIG_SPECIAL,
		OPTION_KEY_CONFIG_JUMP,
		OPTION_KEY_CONFIG_PAUSE,
		OPTION_MAX
	};

	// constructor
	Option(void);

	// destructor
	virtual ~Option(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	void Update(void);

	void Draw(void);

	private:
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
};

#endif	// _OPTION_H_

//---------------------------------- EOF --------------------------------------
