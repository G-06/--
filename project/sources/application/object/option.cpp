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
#include "option/option_bg.h"
#include "option/key_config_ok.h"
#include "option/key_config_cancel.h"
#include "option/key_config_special.h"
#include "option/key_config_jump.h"
#include "option/key_config_pause.h"
#include "option/bgm_volume.h"
#include "option/se_volume.h"
#include "option/option_logo.h"
#include "option/volume_logo.h"
#include "option/keyconfig_logo.h"
#include "system/system.h"
#include "system/direct_input/input_event_buffer.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 Option::DEFAULT_MENU_SIZE = D3DXVECTOR2(300.f, 100.f);
const D3DXVECTOR2 Option::EXPAND_MENU_SIZE = D3DXVECTOR2(450.f, 150.f);

KEY_CONFIG Option::key_config_data_[5];
s32 Option::volume_size_bgm_;
s32 Option::volume_size_se_;
//=============================================================================
// constructor
//=============================================================================
Option::Option(void)
{	
	FILE* fp = fopen("option_data.bin", "rb");

	if(fp == NULL)
	{
		key_config_data_[0].key_code_ = KEY_CODE_OK;
		key_config_data_[0].virtual_num_ = INPUT_EVENT_VIRTUAL_6;
		key_config_data_[0].key_num_ = INPUT_EVENT_PAD_6;
		key_config_data_[0].is_competition_ = false;

		key_config_data_[1].key_code_ = KEY_CODE_NO;
		key_config_data_[1].virtual_num_ = INPUT_EVENT_VIRTUAL_CANCEL;
		key_config_data_[1].key_num_ = INPUT_EVENT_PAD_5;
		key_config_data_[1].is_competition_ = false;
				
		key_config_data_[2].key_code_ = KEY_CODE_LIGHT;
		key_config_data_[2].virtual_num_ = INPUT_EVENT_VIRTUAL_7;
		key_config_data_[2].key_num_ = INPUT_EVENT_PAD_6;
		key_config_data_[2].is_competition_ = true;
				
		key_config_data_[3].key_code_ = KEY_CODE_JUMP;
		key_config_data_[3].virtual_num_ = INPUT_EVENT_VIRTUAL_9;
		key_config_data_[3].key_num_ = INPUT_EVENT_PAD_5;
		key_config_data_[3].is_competition_ = true;
				
		key_config_data_[4].key_code_ = KEY_CODE_PAUSE;
		key_config_data_[4].virtual_num_ = INPUT_EVENT_VIRTUAL_8;
		key_config_data_[4].key_num_ = INPUT_EVENT_PAD_13;
		key_config_data_[4].is_competition_ = true;

		volume_size_bgm_ = 5;
		volume_size_se_ = 5;
	}
	else
	{
		fread(&volume_size_bgm_, sizeof(u32), 1, fp);
		fread(&volume_size_se_, sizeof(u32), 1, fp);
		fread(&key_config_data_[0], sizeof(KEY_CONFIG), 5, fp);
		fclose(fp);
	}

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
	is_indication_ = true;
	is_exchange_ = KEY_CODE_MAX;

	key_config_temp_[0] = key_config_data_[0];
	key_config_temp_[1] = key_config_data_[1];
	key_config_temp_[2] = key_config_data_[2];
	key_config_temp_[3] = key_config_data_[3];
	key_config_temp_[4] = key_config_data_[4];

	bgm_size_temp_ = volume_size_bgm_;
	se_size_temp_ = volume_size_se_;

	bgm_volume_ ->Adjustvolume(bgm_size_temp_);
	se_volume_ ->Adjustvolume(se_size_temp_);

	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_6, INPUT_EVENT_PAD_5);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_6, INPUT_EVENT_PAD_6);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_6, INPUT_EVENT_PAD_7);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_6, INPUT_EVENT_PAD_8);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_6, INPUT_EVENT_PAD_9);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_6, INPUT_EVENT_PAD_10);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_6, INPUT_EVENT_PAD_11);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_6, INPUT_EVENT_PAD_12);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_6, INPUT_EVENT_PAD_13);

	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_7, INPUT_EVENT_PAD_5);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_7, INPUT_EVENT_PAD_6);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_7, INPUT_EVENT_PAD_7);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_7, INPUT_EVENT_PAD_8);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_7, INPUT_EVENT_PAD_9);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_7, INPUT_EVENT_PAD_10);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_7, INPUT_EVENT_PAD_11);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_7, INPUT_EVENT_PAD_12);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_7, INPUT_EVENT_PAD_13);

	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_8, INPUT_EVENT_PAD_5);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_8, INPUT_EVENT_PAD_6);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_8, INPUT_EVENT_PAD_7);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_8, INPUT_EVENT_PAD_8);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_8, INPUT_EVENT_PAD_9);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_8, INPUT_EVENT_PAD_10);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_8, INPUT_EVENT_PAD_11);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_8, INPUT_EVENT_PAD_12);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_8, INPUT_EVENT_PAD_13);

	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_9, INPUT_EVENT_PAD_5);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_9, INPUT_EVENT_PAD_6);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_9, INPUT_EVENT_PAD_7);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_9, INPUT_EVENT_PAD_8);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_9, INPUT_EVENT_PAD_9);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_9, INPUT_EVENT_PAD_10);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_9, INPUT_EVENT_PAD_11);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_9, INPUT_EVENT_PAD_12);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_9, INPUT_EVENT_PAD_13);

	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_CANCEL, INPUT_EVENT_PAD_5);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_CANCEL, INPUT_EVENT_PAD_6);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_CANCEL, INPUT_EVENT_PAD_7);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_CANCEL, INPUT_EVENT_PAD_8);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_CANCEL, INPUT_EVENT_PAD_9);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_CANCEL, INPUT_EVENT_PAD_10);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_CANCEL, INPUT_EVENT_PAD_11);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_CANCEL, INPUT_EVENT_PAD_12);
	GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_CANCEL, INPUT_EVENT_PAD_13);

	GET_DIRECT_INPUT->RegisterInputEventVertual(key_config_temp_[0].virtual_num_, key_config_temp_[0].key_num_);
	GET_DIRECT_INPUT->RegisterInputEventVertual(key_config_temp_[1].virtual_num_, key_config_temp_[1].key_num_);
	GET_DIRECT_INPUT->RegisterInputEventVertual(key_config_temp_[2].virtual_num_, key_config_temp_[2].key_num_);
	GET_DIRECT_INPUT->RegisterInputEventVertual(key_config_temp_[3].virtual_num_, key_config_temp_[3].key_num_);
	GET_DIRECT_INPUT->RegisterInputEventVertual(key_config_temp_[4].virtual_num_, key_config_temp_[4].key_num_);

	GET_DIRECT_INPUT->SaveInputEventVertual();

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

	FILE* fp = fopen("option_data.bin", "wb+");

	fwrite(&volume_size_bgm_, sizeof(u32), 1, fp);
	fwrite(&volume_size_se_, sizeof(u32), 1, fp);
	fwrite(&key_config_data_[0], sizeof(KEY_CONFIG), 5, fp);

	fclose(fp);
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

		if(is_exchange_ == KEY_CODE_MAX)
		{
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
				switch(cursor_y_)
				{
					case Option::OPTION_KEY_CONFIG_OK:
						is_exchange_ = KEY_CODE_OK;
						break;

					case Option::OPTION_KEY_CONFIG_CANCEL:
						is_exchange_ = KEY_CODE_NO;
						break;

					case Option::OPTION_KEY_CONFIG_SPECIAL:
						is_exchange_ = KEY_CODE_LIGHT;
						break;

					case Option::OPTION_KEY_CONFIG_JUMP:
						is_exchange_ = KEY_CODE_JUMP;
						break;

					case Option::OPTION_KEY_CONFIG_PAUSE:
						is_exchange_ = KEY_CODE_PAUSE;
						break;

					default:
						break;
				}
			}

			if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_CANCEL))
			{
				volume_size_bgm_ = bgm_size_temp_;
				volume_size_se_ = se_size_temp_;
				for(s32 i = 0; i < 5; i++)
				{
					key_config_data_[i] = key_config_temp_[i];
				}

				FILE* fp = fopen("option_data.bin", "wb+");
				fwrite(&volume_size_bgm_, sizeof(u32), 1, fp);
				fwrite(&volume_size_se_, sizeof(u32), 1, fp);
				fwrite(&key_config_data_[0], sizeof(KEY_CONFIG), 5, fp);
				fclose(fp);

				__is_indication(false);
			}
		}
		else
		{
			switch(GET_DIRECT_INPUT->GetTrigger(INPUT_EVENT_PAD_3, INPUT_EVENT_PAD_14))
			{
				case INPUT_EVENT_PAD_4:
					Exchange(is_exchange_, INPUT_EVENT_PAD_4);
					is_exchange_ = KEY_CODE_MAX;
					break;

				case INPUT_EVENT_PAD_5:
					Exchange(is_exchange_, INPUT_EVENT_PAD_5);
					is_exchange_ = KEY_CODE_MAX;
					break;

				case INPUT_EVENT_PAD_6:
					Exchange(is_exchange_, INPUT_EVENT_PAD_6);
					is_exchange_ = KEY_CODE_MAX;
					break;

				case INPUT_EVENT_PAD_7:
					Exchange(is_exchange_, INPUT_EVENT_PAD_7);
					is_exchange_ = KEY_CODE_MAX;
					break;

				case INPUT_EVENT_PAD_8:
					Exchange(is_exchange_, INPUT_EVENT_PAD_8);
					is_exchange_ = KEY_CODE_MAX;
					break;

				case INPUT_EVENT_PAD_9:
					Exchange(is_exchange_, INPUT_EVENT_PAD_9);
					is_exchange_ = KEY_CODE_MAX;
					break;

				case INPUT_EVENT_PAD_10:
					Exchange(is_exchange_, INPUT_EVENT_PAD_10);
					is_exchange_ = KEY_CODE_MAX;
					break;

				case INPUT_EVENT_PAD_11:
					Exchange(is_exchange_, INPUT_EVENT_PAD_11);
					is_exchange_ = KEY_CODE_MAX;
					break;

				case INPUT_EVENT_PAD_12:
					Exchange(is_exchange_, INPUT_EVENT_PAD_12);
					is_exchange_ = KEY_CODE_MAX;
					break;

				case INPUT_EVENT_PAD_13:
					Exchange(is_exchange_, INPUT_EVENT_PAD_13);
					is_exchange_ = KEY_CODE_MAX;
					break;

				default:
					break;
			}
		}

		switch(cursor_y_)
		{
			case Option::OPTION_VOLUME_BGM:
				bgm_volume_->Select(true);
				bgm_size_temp_ += cursor_x_;
				if(bgm_size_temp_ > 9)
				{
					bgm_size_temp_ = 9;
				}
				else if(bgm_size_temp_ < 0)
				{
					bgm_size_temp_ = 0;
				}
				bgm_volume_->Adjustvolume(bgm_size_temp_);
				break;

			case Option::OPTION_VOLUME_SE:
				se_volume_->Select(true);
				se_size_temp_ += cursor_x_;
				if(se_size_temp_ > 9)
				{
					se_size_temp_ = 9;
				}
				else if(se_size_temp_ < 0)
				{
					se_size_temp_ = 0;
				}
				se_volume_->Adjustvolume(se_size_temp_);
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
	s32 data_num, data_num2 = 9;
	INPUT_EVENT temp;

	for(s32 i = 0; i < 5; i++)
	{
		GET_DIRECT_INPUT->UnregisterInputEventVertual(key_config_temp_[i].virtual_num_, key_config_temp_[i].key_num_);
	}
	GET_DIRECT_INPUT->SaveInputEventVertual();

	for(s32 i = 0; i < 5; i++)
	{
		if(key_config_temp_[i].key_code_ == code)
		{
			data_num = i;
		}
	}

	for(s32 i = 0; i < 5; i++)
	{
		if(key_config_temp_[i].key_num_ == key_num)
		{
			if(key_config_temp_[data_num].is_competition_ == key_config_temp_[i].is_competition_)
			{
				data_num2 = i;
				break;
			}
		}
	}

	if(data_num2 == 9)
	{
		key_config_temp_[data_num].key_num_ = key_num;
	}
	else
	{
		if(key_config_temp_[data_num2].key_code_ == KEY_CODE_PAUSE || 
				key_config_temp_[data_num2].is_competition_ == key_config_temp_[data_num].is_competition_)
		{
			temp = key_config_temp_[data_num].key_num_;
			key_config_temp_[data_num].key_num_ = key_config_temp_[data_num2].key_num_;	
			key_config_temp_[data_num2].key_num_ = temp;
		}
		else
		{
			key_config_temp_[data_num].key_num_ = key_num;
		}
	}

	for(s32 i = 0; i < 5; i++)
	{
		GET_DIRECT_INPUT->RegisterInputEventVertual(key_config_temp_[i].virtual_num_, key_config_temp_[i].key_num_);
	}
	GET_DIRECT_INPUT->SaveInputEventVertual();

}