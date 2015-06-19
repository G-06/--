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
#include "../option.h"

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
	cancel_button_->__texture_id(Texture::TEXTURE_ID_OPTION_STRING_OP_CANCEL);
	cancel_button_->__point(Sprite::POINT_CENTER);
	cancel_button_->SetParameter();

	set_button_number_ = new Sprite();
	set_button_number_->Initialize();
	set_button_number_->__size(D3DXVECTOR2(75,75));
	set_button_number_->__position(D3DXVECTOR2(cancel_button_->__position().x + 300, cancel_button_->__position().y));
	set_button_number_->__texture_id(Texture::TEXTURE_ID_OPTION_KEY_01);
	set_button_number_->__point(Sprite::POINT_CENTER);
	set_button_number_->SetParameter();

	current_key_event_ = NULL;
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void KeyConfigCancel::Uninitialize(void)
{
	SafeRelease(cancel_button_);
	SafeRelease(set_button_number_);
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
	set_button_number_->Draw();
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
//=============================================================================
// set texture
//=============================================================================
void KeyConfigCancel::__set_button_number_texture(INPUT_EVENT button)
{	
	switch(button)
	{
		case INPUT_EVENT_PAD_4:
			set_button_number_->__texture_id(Texture::TEXTURE_ID_OPTION_KEY_04);
			break;

		case INPUT_EVENT_PAD_5:
			set_button_number_->__texture_id(Texture::TEXTURE_ID_OPTION_KEY_05);
			break;

		case INPUT_EVENT_PAD_6:
			set_button_number_->__texture_id(Texture::TEXTURE_ID_OPTION_KEY_06);
			break;

		case INPUT_EVENT_PAD_7:
			set_button_number_->__texture_id(Texture::TEXTURE_ID_OPTION_KEY_07);
			break;

		case INPUT_EVENT_PAD_8:
			set_button_number_->__texture_id(Texture::TEXTURE_ID_OPTION_KEY_08);
			break;

		case INPUT_EVENT_PAD_9:
			set_button_number_->__texture_id(Texture::TEXTURE_ID_OPTION_KEY_09);
			break;

		case INPUT_EVENT_PAD_10:
			set_button_number_->__texture_id(Texture::TEXTURE_ID_OPTION_KEY_10);
			break;

		case INPUT_EVENT_PAD_11:
			set_button_number_->__texture_id(Texture::TEXTURE_ID_OPTION_KEY_11);

			break;

		case INPUT_EVENT_PAD_12:
			set_button_number_->__texture_id(Texture::TEXTURE_ID_OPTION_KEY_12);

			break;

		case INPUT_EVENT_PAD_13:
			set_button_number_->__texture_id(Texture::TEXTURE_ID_OPTION_KEY_13);
			break;
	}
	set_button_number_->SetParameter();
}


//---------------------------------- EOF --------------------------------------
