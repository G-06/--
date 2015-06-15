//*****************************************************************************
//
// option
//
// Author		: Ryotaro Arai
//
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "option.h"
#include "option_bg.h"
#include "key_config_ok.h"
#include "key_config_cancel.h"
#include "key_config_special.h"
#include "key_config_jump.h"
#include "key_config_pause.h"
#include "bgm_volume.h"
#include "se_volume.h"
#include "option_logo.h"
#include "volume_logo.h"
#include "keyconfig_logo.h"
#include "system/system.h"
#include "system/direct_input/input_event_buffer.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 Option::DEFAULT_MENU_SIZE = D3DXVECTOR2(300.f, 100.f);
const D3DXVECTOR2 Option::EXPAND_MENU_SIZE = D3DXVECTOR2(450.f, 150.f);


//=============================================================================
// constructor
//=============================================================================
Option::Option(void)
{
}

//=============================================================================
// destructor
//=============================================================================
Option::~Option(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool Option::Initialize(void)
{
	option_bg_ = new OptionBg();
	option_bg_->Initialize();

	key_config_ok_ = new KeyConfigOk();
	key_config_ok_->Initialize();

	key_config_cancel_ = new KeyConfigCancel();
	key_config_cancel_->Initialize();

	key_config_special_ = new KeyConfigSpecial();
	key_config_special_->Initialize();

	key_config_pause_ = new KeyConfigPause();
	key_config_pause_->Initialize();

	key_config_jump_ = new KeyConfigJump();
	key_config_jump_->Initialize();

	option_logo_ = new OptionLogo();
	option_logo_->Initialize();

	volume_logo_ = new VolumeLogo();
	volume_logo_->Initialize();

	keyconfig_logo_ = new KeyconfigLogo();
	keyconfig_logo_->Initialize();

	bgm_volume_ = new BgmVolume();
	bgm_volume_->Initialize();

	se_volume_ = new SeVolume();
	se_volume_->Initialize();

	cursor_x_ = 0;
	cursor_y_ = OPTION_VOLUME_BGM;
	is_indication_ = false;
	is_exchange_ = false;

	FILE* fp = fopen("resource/option_data.bin", "rb");

	if(fp == NULL)
	{
		fclose(fp);
		
		key_config_data_[0]->key_code_ = KEY_CODE_OK;
		key_config_data_[0]->virtual_num_ = INPUT_EVENT_VIRTUAL_6;
		key_config_data_[0]->key_num_ = INPUT_EVENT_PAD_6;
		key_config_data_[0]->is_competition_ = false;

		key_config_data_[1]->key_code_ = KEY_CODE_NO;
		key_config_data_[1]->virtual_num_ = INPUT_EVENT_VIRTUAL_CANCEL;
		key_config_data_[1]->key_num_ = INPUT_EVENT_PAD_5;
		key_config_data_[1]->is_competition_ = false;

		key_config_data_[2]->key_code_ = KEY_CODE_LIGHT;
		key_config_data_[2]->virtual_num_ = INPUT_EVENT_VIRTUAL_6;
		key_config_data_[2]->key_num_ = INPUT_EVENT_PAD_6;
		key_config_data_[2]->is_competition_ = true;

		key_config_data_[3]->key_code_ = KEY_CODE_JUMP;
		key_config_data_[3]->virtual_num_ = INPUT_EVENT_VIRTUAL_CANCEL;
		key_config_data_[3]->key_num_ = INPUT_EVENT_PAD_5;
		key_config_data_[3]->is_competition_ = true;

		key_config_data_[4]->key_code_ = KEY_CODE_PAUSE;
		key_config_data_[4]->virtual_num_ = INPUT_EVENT_VIRTUAL_8;
		key_config_data_[4]->key_num_ = INPUT_EVENT_PAD_13;
		key_config_data_[4]->is_competition_ = true;

		volume_size_bgm_ = 5;
		volume_size_se_ = 5;
		bgm_volume_ ->Adjustvolume(volume_size_bgm_);
		se_volume_ ->Adjustvolume(volume_size_se_);
	}
	else
	{
		// fread‚Å“Ç‚Ýž‚Þ
	}

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void Option::Uninitialize(void)
{
	SafeRelease(option_bg_);
	SafeRelease(key_config_ok_);
	SafeRelease(key_config_cancel_);
	SafeRelease(key_config_special_);
	SafeRelease(key_config_pause_);
	SafeRelease(key_config_jump_);
	SafeRelease(option_logo_);
	SafeRelease(volume_logo_);
	SafeRelease(keyconfig_logo_);
	SafeRelease(bgm_volume_);
	SafeRelease(se_volume_);
}

//=============================================================================
// Update
//=============================================================================
void Option::Update(void)
{
	if(is_indication_)
	{
		cursor_x_ = 0;
		key_config_ok_->Select(false);
		key_config_cancel_->Select(false);
		key_config_special_->Select(false);
		key_config_pause_->Select(false);
		key_config_jump_->Select(false);
		bgm_volume_->Select(false);
		se_volume_->Select(false);

		if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_DOWN))
		{
			cursor_y_++;
			if(cursor_y_ >= OPTION_MAX)
			{
				cursor_y_ = OPTION_MIN + 1;
			}
		}

		if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_UP))
		{
			cursor_y_--;
			if(cursor_y_ <= OPTION_MIN)
			{
				cursor_y_ = OPTION_MAX - 1;
			}
		}

		if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_LEFT))
		{
			cursor_x_ = -1;
		}

		if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_RIGHT))
		{
			cursor_x_ = 1;
		}

		if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_6))
		{
			is_exchange_ = true;
		}

		if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_CANCEL))
		{
			__is_indication(false);
		}

		switch(cursor_y_)
		{
			case Option::OPTION_VOLUME_BGM:
				bgm_volume_->Select(true);
				bgm_volume_->Adjustvolume(cursor_x_);
				break;

			case Option::OPTION_VOLUME_SE:
				se_volume_->Select(true);
				se_volume_->Adjustvolume(cursor_x_);
				break;

			case Option::OPTION_KEY_CONFIG_OK:
				key_config_ok_->Select(true);
				break;

			case Option::OPTION_KEY_CONFIG_CANCEL:
				key_config_cancel_->Select(true);
				break;

			case Option::OPTION_KEY_CONFIG_SPECIAL:
				key_config_special_->Select(true);
				break;

			case Option::OPTION_KEY_CONFIG_JUMP:
				key_config_jump_->Select(true);
				break;
		
			case Option::OPTION_KEY_CONFIG_PAUSE:
				key_config_pause_->Select(true);
				break;

		

			default:
				break;
		}
	}
}

//=============================================================================
// Draw
//=============================================================================
void Option::Draw(void)
{
	if(is_indication_)
	{
		option_bg_->Draw();
		key_config_ok_->Draw();
		key_config_cancel_->Draw();
		key_config_special_->Draw();
		key_config_pause_->Draw();
		key_config_jump_->Draw();
		option_logo_->Draw();
		volume_logo_->Draw();
		keyconfig_logo_->Draw();
		bgm_volume_->Draw();
		se_volume_->Draw();
	}
}

//=============================================================================
// Exchange
//=============================================================================
void Option::Exchange(KEY_CODE code, INPUT_EVENT key_num)
{
	s32 data_num;
	INPUT_EVENT temp;

	for(s32 i = 0; i < 5; i++)
	{
		if(key_config_data_[i]->key_code_ == code)
		{
			data_num = i;
		}
	}

	for(s32 i = 0; i < 5; i++)
	{
		if(key_config_data_[i]->key_num_ == key_num)
		{
			if(key_config_data_[i]->key_code_ == KEY_CODE_PAUSE || 
				key_config_data_[i]->is_competition_ == key_config_data_[data_num]->is_competition_)
			{
				temp = key_config_data_[data_num]->key_num_;

				GET_DIRECT_INPUT->UnregisterInputEventVertual(key_config_data_[data_num]->virtual_num_, key_config_data_[data_num]->key_num_);
				GET_DIRECT_INPUT->RegisterInputEventVertual(key_config_data_[data_num]->virtual_num_, key_config_data_[i]->key_num_);

				key_config_data_[data_num]->key_num_ = key_config_data_[i]->key_num_;

				GET_DIRECT_INPUT->UnregisterInputEventVertual(key_config_data_[i]->virtual_num_, key_config_data_[i]->key_num_);
				GET_DIRECT_INPUT->RegisterInputEventVertual(key_config_data_[i]->virtual_num_, temp);
				GET_DIRECT_INPUT->SaveInputEventVertual();
				
				key_config_data_[i]->key_num_ = temp;
			}
			else
			{
				GET_DIRECT_INPUT->UnregisterInputEventVertual(key_config_data_[i]->virtual_num_,key_config_data_[i]->key_num_);
				GET_DIRECT_INPUT->RegisterInputEventVertual(key_config_data_[data_num]->virtual_num_, key_config_data_[i]->key_num_);
				GET_DIRECT_INPUT->SaveInputEventVertual();

				key_config_data_[i]->key_num_ = key_num;
			}
		}
	}
		
	FILE* fp = fopen("resource/option_data.bin", "rb");

	fwrite(&volume_size_bgm_, sizeof(u32), 1, fp);
	fwrite(&volume_size_se_, sizeof(u32), 1, fp);
	fwrite(&key_config_data_[0], sizeof(KEY_CONFIG), 5, fp);

	fclose(fp);

}