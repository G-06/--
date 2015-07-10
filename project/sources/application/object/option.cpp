//*****************************************************************************
//
// option
//
// Author		: Ryotaro Arai
//				: masato masuda
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

#include "../object/option/option_sprite_smooth.h"
#include "application/object/message_window.h"
#include "option/option_decide.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const f32 MENU_SCALE = 0.9f;
const D3DXVECTOR2 Option::DEFAULT_MENU_SIZE = D3DXVECTOR2(256.0f * MENU_SCALE, 64.0f * MENU_SCALE);
const D3DXVECTOR2 Option::EXPAND_MENU_SIZE = D3DXVECTOR2(450.f, 150.f);
const f32 Option::VOLUME_MIN	= 0.0f;
const f32 Option::VOLUME_MAX	= 1.0f;
const f32 Option::VOLUME_RATE	= VOLUME_MAX / 10;
const u32 DEST_FRAME_COUNT = 20;				// ウィンドウ開閉の時間

//=============================================================================
// constructor
//=============================================================================
Option::Option(void)
	:cursor_y_(0)
	,select_menu_alpha_(1)
	,plus_alpha_(-0.05f)
	,option_bg_(NULL)
	,option_logo_(NULL)
	,volume_logo_(NULL)
	,keyconfig_logo_(NULL)
	,key_config_ok_(NULL)
	,key_config_cancel_(NULL)
	,key_config_special_(NULL)
	,key_config_pause_(NULL)
	,key_config_jump_(NULL)
	,message_window_(NULL)
	,option_decide_(NULL)
	,mode_(OPTION_MODE_OPTION)
	,bgm_size_temp_(0.0f)
	,se_size_temp_(0.0f)
{
	option_data_._bgm_volume = 1.0f;
	option_data_._se_volume  = 1.0f;
	option_data_._decide_key = INPUT_EVENT_PAD_6;
	option_data_._cancel_key = INPUT_EVENT_PAD_5;
	option_data_._light_key  = INPUT_EVENT_PAD_9;
	option_data_._pause_key  = INPUT_EVENT_PAD_13;
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

	option_decide_ = new OptionDecide();
	option_decide_->Initialize();

	cursor_x_ = 0;
	cursor_y_ = OPTION_VOLUME_BGM;
	is_indication_ = false;
	is_exchange_ = KEY_CODE_MAX;

	option_data_ = *GET_OPTION_DATA;

	// position
	const D3DXVECTOR2 MENU_OFFSETT = D3DXVECTOR2(400.0f, 10.0f);

	const D3DXVECTOR2 DEF_LOGO_POS = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f - 250, 160.f);
	volume_logo_->__position(D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f - 320.0f, DEF_LOGO_POS.y - 60.0f));
	bgm_volume_->__position(D3DXVECTOR2(DEF_LOGO_POS.x, DEF_LOGO_POS.y), 300.0f);
	se_volume_->__position(D3DXVECTOR2(DEF_LOGO_POS.x, DEF_LOGO_POS.y + DEFAULT_MENU_SIZE.y + MENU_OFFSETT.y), 300.0f);

	const D3DXVECTOR2 DEF_MENU_POS = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f - 250, 360.0f);
	keyconfig_logo_->__position(D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f - 275.0f, 300.f));
	key_config_ok_->__position(D3DXVECTOR2(DEF_MENU_POS.x, DEF_MENU_POS.y), MENU_OFFSETT.x);
	key_config_cancel_->__position(D3DXVECTOR2(DEF_MENU_POS.x, DEF_MENU_POS.y + DEFAULT_MENU_SIZE.y + MENU_OFFSETT.y), MENU_OFFSETT.x);
	key_config_special_->__position(D3DXVECTOR2(DEF_MENU_POS.x, DEF_MENU_POS.y + (DEFAULT_MENU_SIZE.y + MENU_OFFSETT.y) * 2), MENU_OFFSETT.x);
	key_config_pause_->__position(D3DXVECTOR2(DEF_MENU_POS.x, DEF_MENU_POS.y + (DEFAULT_MENU_SIZE.y + MENU_OFFSETT.y) * 3), MENU_OFFSETT.x);

	// decide
	option_decide_->__position(D3DXVECTOR2(DEF_MENU_POS.x, DEF_MENU_POS.y + (DEFAULT_MENU_SIZE.y + MENU_OFFSETT.y) * 4), MENU_OFFSETT.x);

	// message_window
	message_window_ = new MessageWindow();
	message_window_->Initialize();
	message_window_->__dest_frame_count(DEST_FRAME_COUNT);

	is_select_ = true;
	bgm_volume_->Select(true);
	bgm_volume_->Adjustvolume(option_data_._bgm_volume);
	se_volume_->Adjustvolume(option_data_._se_volume);
	key_config_ok_->__set_button_number_texture(option_data_._decide_key);
	key_config_cancel_->__set_button_number_texture(option_data_._cancel_key);
	key_config_special_->__set_button_number_texture(option_data_._light_key);
	key_config_pause_->__set_button_number_texture(option_data_._pause_key);

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
	SafeRelease(message_window_);
	SafeRelease(option_decide_);
}

//=============================================================================
// Update
//=============================================================================
void Option::Update(void)
{
	if(is_indication_)
	{
		key_config_ok_->Select(false);
		key_config_cancel_->Select(false);
		key_config_special_->Select(false);
		key_config_pause_->Select(false);
		key_config_jump_->Select(false);
		bgm_volume_->Select(false);
		se_volume_->Select(false);
		option_decide_->Select(false);

		if(is_select_)
		{
			if(mode_ == OPTION_MODE_OPTION)
			{
				if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_DOWN))
				{
					cursor_y_++;
				}

				if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_UP))
				{
					cursor_y_--;
				}
				if(cursor_y_ >= OPTION_MAX)
				{
					cursor_y_ = OPTION_MIN + 1;
				}

				if(cursor_y_ <= OPTION_MIN)
				{
					cursor_y_ = OPTION_MAX - 1;
				}

				switch(cursor_y_)
				{
					case Option::OPTION_VOLUME_BGM:
					{
						bgm_volume_->Select(true);
						if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_LEFT))
						{
							option_data_._bgm_volume -= VOLUME_RATE;
						}
						if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_RIGHT))
						{
							option_data_._bgm_volume += VOLUME_RATE;
						}

						if(option_data_._bgm_volume > VOLUME_MAX)
						{
							option_data_._bgm_volume = VOLUME_MAX;
						}

						if(option_data_._bgm_volume < VOLUME_MIN)
						{
							option_data_._bgm_volume = VOLUME_MIN;
						}
						bgm_volume_->Adjustvolume(option_data_._bgm_volume);
						GET_BGM->SetVolume(option_data_._bgm_volume);
						break;
					}
					case Option::OPTION_VOLUME_SE:
					{
						se_volume_->Select(true);

						if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_LEFT))
						{
							option_data_._se_volume -= VOLUME_RATE;
						}
						if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_RIGHT))
						{
							option_data_._se_volume += VOLUME_RATE;
						}

						if(option_data_._se_volume > VOLUME_MAX)
						{
							option_data_._se_volume = VOLUME_MAX;
						}

						if(option_data_._se_volume < VOLUME_MIN)
						{
							option_data_._se_volume = VOLUME_MIN;
						}
						se_volume_->Adjustvolume(option_data_._se_volume);
						GET_SE->SetVolume(option_data_._se_volume);

						break;
					}
					case Option::OPTION_KEY_CONFIG_OK:
					{
						key_config_ok_->Select(true);
						if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_DECIDE))
						{
							is_select_ = false;
						}
						break;
					}
					case Option::OPTION_KEY_CONFIG_CANCEL:
					{
						key_config_cancel_->Select(true);
						if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_DECIDE))
						{
							is_select_ = false;
						}
						break;
					}
					case Option::OPTION_KEY_CONFIG_SPECIAL:
					{
						key_config_special_->Select(true);
						if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_DECIDE))
						{
							is_select_ = false;
						}
						break;
					}
					case Option::OPTION_KEY_CONFIG_PAUSE:
					{
						key_config_pause_->Select(true);
						if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_DECIDE))
						{
							is_select_ = false;
						}
						break;
					}
					case OPTION_DECIDE:
					{
						option_decide_->Select(true);
						if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_DECIDE))
						{
							mode_ = OPTION_MODE_DECIDE;
							message_window_->Show();
						}
						break;
					}
					default:
					{
						break;
					}
				}

				// cancel
				if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_CANCEL))
				{
					mode_ = OPTION_MODE_CANCEL;
					message_window_->Show();
				}
			}
			else if(mode_ == OPTION_MODE_CANCEL)
			{
				UpdateModeCancel();
			}
			else if(mode_ == OPTION_MODE_DECIDE)
			{
				UpdateModeDecide();
			}
		}
		// キー変更入力
		else
		{
			if(select_menu_alpha_ + plus_alpha_ > 1.0f || select_menu_alpha_ + plus_alpha_ < 0.0f)
			{
				plus_alpha_ *= -1;
			}
			select_menu_alpha_ += plus_alpha_;

			INPUT_EVENT input_event = GET_DIRECT_INPUT->GetTrigger(INPUT_EVENT_PAD_4,INPUT_EVENT_PAD_25);

			switch(cursor_y_)
			{
				case Option::OPTION_KEY_CONFIG_OK:
				{
					key_config_ok_->SetAlpha(select_menu_alpha_);
					key_config_ok_->Select(true);
					key_config_ok_->__texture_id_frame(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_002);
					if(input_event != INPUT_EVENT_MAX)
					{
						key_config_ok_->__texture_id_frame(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_001);
						Exchange(&option_data_._decide_key,input_event);
						is_select_ = true;
						key_config_ok_->SetAlpha(1.0f);
					}
					break;
				}
				case Option::OPTION_KEY_CONFIG_CANCEL:
				{
					key_config_cancel_->SetAlpha(select_menu_alpha_);
					key_config_cancel_->Select(true);
					key_config_cancel_->__texture_id_frame(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_002);
					if(input_event != INPUT_EVENT_MAX)
					{
						key_config_cancel_->__texture_id_frame(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_001);
						Exchange(&option_data_._cancel_key,input_event);
						is_select_ = true;
						key_config_cancel_->SetAlpha(1.0f);
					}
					break;
				}
				case Option::OPTION_KEY_CONFIG_SPECIAL:
				{
					key_config_special_->SetAlpha(select_menu_alpha_);
					key_config_special_->Select(true);
					key_config_special_->__texture_id_frame(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_002);
					if(input_event != INPUT_EVENT_MAX)
					{
						key_config_special_->__texture_id_frame(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_001);
						Exchange(&option_data_._light_key,input_event);
						is_select_ = true;
						key_config_special_->SetAlpha(1.0f);
					}
					break;
				}
				case Option::OPTION_KEY_CONFIG_PAUSE:
				{
					key_config_pause_->SetAlpha(select_menu_alpha_);
					key_config_pause_->Select(true);
					key_config_pause_->__texture_id_frame(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_002);
					if(input_event != INPUT_EVENT_MAX)
					{
						key_config_pause_->__texture_id_frame(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_001);
						Exchange(&option_data_._pause_key,input_event);
						is_select_ = true;
						key_config_pause_->SetAlpha(1.0f);
					}
					break;
				}
				default:
				{
					break;
				}
			}
		} // is_select_
	} // is_indication_

	option_bg_->Update();
	key_config_ok_->Update();
	key_config_cancel_->Update();
	key_config_special_->Update();
	key_config_pause_->Update();
	//key_config_jump_->Update();
	option_logo_->Update();
	volume_logo_->Update();
	keyconfig_logo_->Update();
	bgm_volume_->Update();
	se_volume_->Update();
	option_decide_->Update();

	key_config_ok_->__set_button_number_texture(option_data_._decide_key);
	key_config_cancel_->__set_button_number_texture(option_data_._cancel_key);
	key_config_special_->__set_button_number_texture(option_data_._light_key);
	key_config_pause_->__set_button_number_texture(option_data_._pause_key);

	// message_window
	message_window_->Update();
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
		//key_config_jump_->Draw();
		option_logo_->Draw();
		volume_logo_->Draw();
		keyconfig_logo_->Draw();
		bgm_volume_->Draw();
		se_volume_->Draw();
		option_decide_->Draw();

		message_window_->Draw();
	}
}

//=============================================================================
// Exchange
//=============================================================================
void Option::Exchange(INPUT_EVENT* out_input_event,INPUT_EVENT input_event)
{
	if(option_data_._decide_key == input_event)
	{
		option_data_._decide_key = *out_input_event;
	}

	if(option_data_._cancel_key == input_event)
	{
		option_data_._cancel_key = *out_input_event;
	}

	if(option_data_._light_key == input_event)
	{
		option_data_._light_key = *out_input_event;
	}

	if(option_data_._pause_key == input_event)
	{
		option_data_._pause_key = *out_input_event;
	}

	*out_input_event = input_event;
}

//=============================================================================
// Load
//=============================================================================
void Option::Load(void)
{
	FILE* fp = fopen("data/option_data.bin", "rb");

	if(fp == nullptr)
	{
		return;
	}
	else
	{
		fread(&option_data_,sizeof(option_data_),1,fp);
		fclose(fp);
	}

	//GET_DIRECT_INPUT->RegisterInputEventVertual(key_config_temp_[0].virtual_num_, key_config_temp_[0].key_num_);
	//GET_DIRECT_INPUT->RegisterInputEventVertual(key_config_temp_[1].virtual_num_, key_config_temp_[1].key_num_);
	//GET_DIRECT_INPUT->RegisterInputEventVertual(key_config_temp_[2].virtual_num_, key_config_temp_[2].key_num_);
	//GET_DIRECT_INPUT->RegisterInputEventVertual(key_config_temp_[3].virtual_num_, key_config_temp_[3].key_num_);
	//GET_DIRECT_INPUT->RegisterInputEventVertual(key_config_temp_[4].virtual_num_, key_config_temp_[4].key_num_);

	//GET_DIRECT_INPUT->SaveInputEventVertual();
}

//=============================================================================
// UpdateModeDecide
//-----------------------------------------------------------------------------
// 設定を保存する？のメッセージウィンドウ
//=============================================================================
void Option::UpdateModeDecide(void)
{
	option_decide_->__texture_id_frame(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_002);

	// ウィンドウのタイトル
	message_window_->__title_texture_id_(Texture::TEXTURE_ID_STRING_OP_CONFIRM_SAVE);

	// yes no の選択
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_LEFT))
	{
		message_window_->SelectDown();
	}
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_RIGHT))
	{
		message_window_->SelectUp();
	}

	// 決定
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_DECIDE))
	{
		// YES
		if(message_window_->__is_select() == MessageWindow::MESSAGE_YES)
		{
			// 枠色変更
			message_window_->__select_frame_texture_id_(message_window_->__is_select(), Texture::TEXTURE_ID_TITLE_SELECT_FRAME_002);

			mode_ = OPTION_MODE_OPTION;
			message_window_->ForcingClose();
			is_indication_ = false;
			cursor_y_ = 0;

			// save
			OPTION_DATA* option_data = GET_OPTION_DATA;

			GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_DECIDE,option_data->_decide_key);
			GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_CANCEL,option_data->_cancel_key);
			GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_LIGHT ,option_data->_light_key);
			GET_DIRECT_INPUT->UnregisterInputEventVertual(INPUT_EVENT_VIRTUAL_PAUSE ,option_data->_pause_key);

			GET_DIRECT_INPUT->RegisterInputEventVertual(INPUT_EVENT_VIRTUAL_DECIDE,option_data_._decide_key);
			GET_DIRECT_INPUT->RegisterInputEventVertual(INPUT_EVENT_VIRTUAL_CANCEL,option_data_._cancel_key);
			GET_DIRECT_INPUT->RegisterInputEventVertual(INPUT_EVENT_VIRTUAL_LIGHT,option_data_._light_key);
			GET_DIRECT_INPUT->RegisterInputEventVertual(INPUT_EVENT_VIRTUAL_PAUSE,option_data_._pause_key);

			*option_data = option_data_;

			FILE* fp = fopen("data/system/option_data.bin","wb");

			if(fp != nullptr)
			{
				fwrite(&option_data_,sizeof(OPTION_DATA),1,fp);
				fclose(fp);
			}
		}
		// NO
		else if(message_window_->__is_select() == MessageWindow::MESSAGE_NO)
		{
			// 枠色変更
			message_window_->__select_frame_texture_id_(message_window_->__is_select(), Texture::TEXTURE_ID_TITLE_SELECT_FRAME_002);

			// ウィンドウを閉じる
			if(message_window_->__is_move() == false)
			{
				message_window_->Close();
				mode_ = OPTION_MODE_OPTION;
			}
		}
	}

	// キャンセル
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_CANCEL))
	{
		if(message_window_->__is_move() == false)
		{
			message_window_->Close();
			mode_ = OPTION_MODE_OPTION;
		}
	}
}

//=============================================================================
// UpdateModeCancel
//-----------------------------------------------------------------------------
// 変更キャンセルして戻る？のメッセージウィンドウ
//=============================================================================
void Option::UpdateModeCancel(void)
{
	switch(cursor_y_)
	{
		case Option::OPTION_VOLUME_BGM:
		{
			bgm_volume_->Select(true);
			break;
		}
		case Option::OPTION_VOLUME_SE:
		{
			se_volume_->Select(true);
			break;
		}
		case Option::OPTION_KEY_CONFIG_OK:
		{
			key_config_ok_->Select(true);
			break;
		}
		case Option::OPTION_KEY_CONFIG_CANCEL:
		{
			key_config_cancel_->Select(true);
			break;
		}
		case Option::OPTION_KEY_CONFIG_SPECIAL:
		{
			key_config_special_->Select(true);
			break;
		}
		case Option::OPTION_KEY_CONFIG_PAUSE:
		{
			key_config_pause_->Select(true);
			break;
		}
		case OPTION_DECIDE:
		{
			option_decide_->Select(true);
			break;
		}
		default:
		{
			break;
		}
	}

	// ウィンドウのタイトル
	message_window_->__title_texture_id_(Texture::TEXTURE_ID_STRING_OP_CONFIRM_CANCEL);

	// yes no の選択
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_LEFT))
	{
		message_window_->SelectDown();
	}
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_RIGHT))
	{
		message_window_->SelectUp();
	}

	// 決定
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_DECIDE))
	{
		// YES
		if(message_window_->__is_select() == MessageWindow::MESSAGE_YES)
		{
			// 枠色変更
			message_window_->__select_frame_texture_id_(message_window_->__is_select(), Texture::TEXTURE_ID_TITLE_SELECT_FRAME_002);

			// sonnd volume 戻す
			GET_BGM->SetVolume(bgm_size_temp_);
			GET_SE->SetVolume(se_size_temp_);
			bgm_volume_->Adjustvolume(bgm_size_temp_);
			se_volume_->Adjustvolume(se_size_temp_);

			mode_ = OPTION_MODE_OPTION;
			message_window_->ForcingClose();
			is_indication_ = false;
			cursor_y_ = 0;
		}
		// NO
		else if(message_window_->__is_select() == MessageWindow::MESSAGE_NO)
		{
			// 枠色変更
			message_window_->__select_frame_texture_id_(message_window_->__is_select(), Texture::TEXTURE_ID_TITLE_SELECT_FRAME_002);

			// ウィンドウを閉じる
			if(message_window_->__is_move() == false)
			{
				message_window_->Close();
				mode_ = OPTION_MODE_OPTION;
			}
		}
	}

	// キャンセル
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_CANCEL))
	{
		if(message_window_->__is_move() == false)
		{
			message_window_->Close();
			mode_ = OPTION_MODE_OPTION;
		}
	}
}

//=============================================================================
// __is_indication
//-----------------------------------------------------------------------------
//=============================================================================
void Option::__is_indication(const bool indication)
{
	is_indication_ = indication;

	// オプションのキー設定を取ってくる
	if(indication){
		option_data_ = *GET_OPTION_DATA;
		bgm_size_temp_ = option_data_._bgm_volume;
		se_size_temp_ = option_data_._se_volume;
	}
}


// EOF