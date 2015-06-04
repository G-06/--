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
#include "system/system.h"
#include "system/direct_input/input_event_buffer.h"

//*****************************************************************************
// constant definition
//*****************************************************************************


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
}

//=============================================================================
// Update
//=============================================================================
void Option::Update(void)
{
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_RIGHT))
	{
		cursor_++;
	}

	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_RIGHT))
	{
		cursor_--;
	}

	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_6))
	{
		
	}

	switch(option_scene_)
	{
		case Option::OPTION_MENU:
			break;

		case Option::OPTION_CONFIG_1:
			break;

		case Option::OPTION_CONFIG_2:
			break;

		case Option::OPTION_VOLUME:
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

		case Option::OPTION_CONFIG_1:
			break;

		case Option::OPTION_CONFIG_2:
			break;

		case Option::OPTION_VOLUME:
			break;

		default:
			break;
	}

}