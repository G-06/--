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
#include "option_menu.h"
#include "option_config_menu.h"
#include "option_volume.h"
#include "system/system.h"
#include "system/direct_input/input_event_buffer.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 Option::DEFAULT_MENU_SIZE = D3DXVECTOR2(200.f, 50.f);
const D3DXVECTOR2 Option::EXPAND_MENU_SIZE = D3DXVECTOR2(300.f, 100.f);


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

	option_menu_ = new OptionMenu();
	option_menu_->Initialize();

	option_config_menu_ = new OptionConfigMenu();
	option_config_menu_->Initialize();

	option_volume_ = new OptionVolume();
	option_volume_->Initialize();

	option_scene_ = OPTION_MENU;
	cursor_ = 0;

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void Option::Uninitialize(void)
{
	SafeRelease(option_bg_);
	SafeRelease(option_menu_);
	SafeRelease(option_config_menu_);
	SafeRelease(option_volume_);
}

//=============================================================================
// Update
//=============================================================================
void Option::Update(void)
{
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_DOWN))
	{
		cursor_++;
	}

	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_UP))
	{
		cursor_--;
	}

	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_6))
	{
		switch(option_scene_)
		{
			case Option::OPTION_MENU:
				if(cursor_ == 0)
				{
					cursor_ = 0;
					option_scene_ = OPTION_KEY_CONFIG;
				}
				break;


			case Option::OPTION_VOLUME:
				break;
		}
	}

	switch(option_scene_)
	{
		case Option::OPTION_MENU:
			if(cursor_ >= Option::MENU_MAX)
			{
				cursor_ = Option::MENU_MIN + 1;
			}
			else if(cursor_ <= Option::MENU_MIN)
			{
				cursor_ = Option::MENU_MAX - 1;
			}
			option_menu_->Select(cursor_);
			break;

		case Option::OPTION_KEY_CONFIG:
			if(cursor_ >= OptionConfigMenu::BUTTON_MAX)
			{
				cursor_ = Option::MENU_MIN + 1;
			}
			else if(cursor_ <= Option::MENU_MIN)
			{
				cursor_ = Option::MENU_MAX - 1;
			}
			option_config_menu_->Select(cursor_);
			break;

		case Option::OPTION_VOLUME:
			if(cursor_ > 9)
			{
				cursor_ = 9;
			}
			else if(cursor_ < 0)
			{
				cursor_ = 0;
			}
			option_volume_->Adjustvolume(cursor_);
			break;

		default:
			break;
	}
}

//=============================================================================
// Draw
//=============================================================================
void Option::Draw(void)
{
	option_bg_->Draw();

	switch(option_scene_)
	{
		case Option::OPTION_MENU:
			option_menu_->Draw();
			break;

		case Option::OPTION_KEY_CONFIG:
			option_config_menu_->Draw();
			break;

		case Option::OPTION_VOLUME:
			option_volume_->Draw();
			break;

		default:
			break;
	}

}