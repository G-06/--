//*****************************************************************************
//
// key config cancel
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "key_config_cancel.h"
#include "render/sprite.h"
#include "system/system.h"
#include "option.h"

//=============================================================================
// constructor
//=============================================================================
KeyConfigCancel::KeyConfigCancel(void)
{
}

//=============================================================================
// destructor
//=============================================================================
KeyConfigCancel::~KeyConfigCancel(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool KeyConfigCancel::Initialize(void)
{
	cancel_button_ = new Sprite();
	cancel_button_->Initialize();
	cancel_button_->__size(Option::DEFAULT_MENU_SIZE);
	cancel_button_->__position(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width()/2 - 250,425.0f));
	cancel_button_->__texture_id(Texture::TEXTURE_ID_CANCEL_BUTTON);
	cancel_button_->__point(Sprite::POINT_CENTER);
	cancel_button_->SetParameter();

	current_key_event_ = NULL;
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void KeyConfigCancel::Uninitialize(void)
{
	SafeRelease(cancel_button_);
}

//=============================================================================
// update
//=============================================================================
void KeyConfigCancel::Update(void)
{
}

//=============================================================================
// draw
//=============================================================================
void KeyConfigCancel::Draw(void)
{
	cancel_button_->Draw();
}

//=============================================================================
// select
//=============================================================================
void KeyConfigCancel::Select(bool is_select)
{
	if(is_select == true)
	{
		cancel_button_->__size(Option::EXPAND_MENU_SIZE);
	}
	else
	{
		cancel_button_->__size(Option::DEFAULT_MENU_SIZE);
	}
	
	cancel_button_->SetParameter();
}

//---------------------------------- EOF --------------------------------------
