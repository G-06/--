//*****************************************************************************
//
// key config jump
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "key_config_jump.h"
#include "render/sprite.h"
#include "../option.h"

//=============================================================================
// constructor
//=============================================================================
KeyConfigJump::KeyConfigJump(void)
{
}

//=============================================================================
// destructor
//=============================================================================
KeyConfigJump::~KeyConfigJump(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool KeyConfigJump::Initialize(void)
{
	jump_button_ = new Sprite();
	jump_button_->Initialize();
	jump_button_->__size(Option::DEFAULT_MENU_SIZE);
	jump_button_->__position(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width()/2 - 250,525.0f));
	jump_button_->__texture_id(Texture::TEXTURE_ID_OPTION_STRING_OP_JUMP);
	jump_button_->__point(Sprite::POINT_CENTER);
	jump_button_->SetParameter();

	set_button_number_ = new Sprite();
	set_button_number_->Initialize();
	set_button_number_->__size(D3DXVECTOR2(75,75));
	set_button_number_->__position(D3DXVECTOR2(jump_button_->__position().x + 300, jump_button_->__position().y));
	set_button_number_->__texture_id(Texture::TEXTURE_ID_OPTION_KEY_01);
	set_button_number_->__point(Sprite::POINT_CENTER);
	set_button_number_->SetParameter();

	current_key_event_ = NULL;
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void KeyConfigJump::Uninitialize(void)
{
	SafeRelease(jump_button_);
	SafeRelease(set_button_number_);
}

//=============================================================================
// update
//=============================================================================
void KeyConfigJump::Update(void)
{
}

//=============================================================================
// draw
//=============================================================================
void KeyConfigJump::Draw(void)
{
	jump_button_->Draw();
	set_button_number_->Draw();
}

//=============================================================================
// select
//=============================================================================
void KeyConfigJump::Select(bool is_select)
{
	if(is_select == true)
	{
		jump_button_->__size(Option::EXPAND_MENU_SIZE);
	}
	else
	{
		jump_button_->__size(Option::DEFAULT_MENU_SIZE);
	}
	
	jump_button_->SetParameter();
}

//=============================================================================
// set texture
//=============================================================================
void KeyConfigJump::__set_button_number_texture(INPUT_EVENT button)
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
void KeyConfigJump::SetAlpha(f32 alpha)
{
	jump_button_->__color(D3DXCOLOR(1,1,1,alpha));

	jump_button_->SetParameter();
}

//---------------------------------- EOF --------------------------------------
