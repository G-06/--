//*****************************************************************************
//
// key config pause
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "key_config_pause.h"
#include "render/sprite.h"
#include "system/system.h"
#include "option.h"

//=============================================================================
// constructor
//=============================================================================
KeyConfigPause::KeyConfigPause(void)
{
}

//=============================================================================
// destructor
//=============================================================================
KeyConfigPause::~KeyConfigPause(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool KeyConfigPause::Initialize(void)
{
	pause_button_ = new Sprite();
	pause_button_->Initialize();
	pause_button_->__size(Option::DEFAULT_MENU_SIZE);
	pause_button_->__position(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width()/2 - 250,575.0f));
	pause_button_->__texture_id(Texture::TEXTURE_ID_PAUSE_BUTTON);
	pause_button_->__point(Sprite::POINT_CENTER);
	pause_button_->SetParameter();

	current_key_event_ = NULL;
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void KeyConfigPause::Uninitialize(void)
{
	SafeRelease(pause_button_);
}

//=============================================================================
// update
//=============================================================================
void KeyConfigPause::Update(void)
{
}

//=============================================================================
// draw
//=============================================================================
void KeyConfigPause::Draw(void)
{
	pause_button_->Draw();
}

//=============================================================================
// select
//=============================================================================
void KeyConfigPause::Select(bool is_select)
{
	if(is_select == true)
	{
		pause_button_->__size(Option::EXPAND_MENU_SIZE);
	}
	else
	{
		pause_button_->__size(Option::DEFAULT_MENU_SIZE);
	}
	
	pause_button_->SetParameter();
}

//---------------------------------- EOF --------------------------------------
