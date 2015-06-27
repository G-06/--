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
#include "../option.h"

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
	pause_button_->__position(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width()/2 - 250,525.0f));
	pause_button_->__texture_id(Texture::TEXTURE_ID_OPTION_STRING_OP_PAUSE);
	pause_button_->__point(Sprite::POINT_CENTER);
	pause_button_->SetParameter();

	set_button_number_ = new Sprite();
	set_button_number_->Initialize();
	set_button_number_->__size(D3DXVECTOR2(75,75));
	set_button_number_->__position(D3DXVECTOR2(pause_button_->__position().x + 300, pause_button_->__position().y));
	set_button_number_->__texture_id(Texture::TEXTURE_ID_OPTION_KEY_01);
	set_button_number_->__point(Sprite::POINT_CENTER);
	set_button_number_->SetParameter();

	current_key_event_ = NULL;

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void KeyConfigPause::Uninitialize(void)
{
	SafeRelease(pause_button_);
	SafeRelease(set_button_number_);
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
	set_button_number_->Draw();
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

//=============================================================================
// set texture
//=============================================================================
void KeyConfigPause::__set_button_number_texture(INPUT_EVENT button)
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

		case INPUT_EVENT_PAD_14:
			set_button_number_->__texture_id(Texture::TEXTURE_ID_OPTION_KEY_14);
			break;

		case INPUT_EVENT_PAD_15:
			set_button_number_->__texture_id(Texture::TEXTURE_ID_NONE);
			break;
	}
	set_button_number_->SetParameter();
}


//=============================================================================
// set alpha
//=============================================================================
void KeyConfigPause::SetAlpha(f32 alpha)
{
	pause_button_->__color(D3DXCOLOR(1,1,1,alpha));

	pause_button_->SetParameter();
}


//---------------------------------- EOF --------------------------------------
