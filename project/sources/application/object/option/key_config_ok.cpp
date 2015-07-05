//*****************************************************************************
//
// key config ok
//
// Author		: Ryotaro Arai
//				: masato masuda
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "key_config_ok.h"
#include "render/sprite.h"
#include "../option.h"
#include "object/option/option_sprite_smooth.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
// string
const D3DXVECTOR2 DEFAULT_SIZE = Option::DEFAULT_MENU_SIZE;
const D3DXVECTOR2 DEFAULT_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f - 250, 375.0f);
// number
const D3DXVECTOR2 DEFAULT_NUM_SIZE = D3DXVECTOR2(75.0f, 75.0f);
const D3DXVECTOR2 DEFAULT_NUM_POSITION = D3DXVECTOR2(DEFAULT_POSITION.x + 300.0f, DEFAULT_POSITION.y);


//=============================================================================
// constructor
//=============================================================================
KeyConfigOk::KeyConfigOk(void)
	:select_button_(NULL)
	,select_button_frame_(NULL)
	,set_button_number_(NULL)
	,set_button_number_frame_(NULL)
	,current_key_event_(NULL)
{
}

//=============================================================================
// destructor
//=============================================================================
KeyConfigOk::~KeyConfigOk(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool KeyConfigOk::Initialize(void)
{
	select_button_ = new OptionSpriteSmooth();
	select_button_->Initialize();
	select_button_->__size(DEFAULT_SIZE);
	select_button_->__position(DEFAULT_POSITION);
	select_button_->__texture_id(Texture::TEXTURE_ID_OPTION_STRING_OP_DECIDE);

	select_button_frame_ = new OptionSpriteSmooth();
	select_button_frame_->Initialize();
	select_button_frame_->__size(DEFAULT_SIZE);
	select_button_frame_->__position(DEFAULT_POSITION);
	select_button_frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_000);

	set_button_number_ = new OptionSpriteSmooth();
	set_button_number_->Initialize();
	set_button_number_->__size(DEFAULT_NUM_SIZE);
	set_button_number_->__position(DEFAULT_NUM_POSITION);
	set_button_number_->__texture_id(Texture::TEXTURE_ID_OPTION_KEY_01);

	set_button_number_frame_ = new OptionSpriteSmooth();
	set_button_number_frame_->Initialize();
	set_button_number_frame_->__size(DEFAULT_NUM_SIZE);
	set_button_number_frame_->__position(DEFAULT_NUM_POSITION);
	set_button_number_frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_000);

	current_key_event_ = NULL;
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void KeyConfigOk::Uninitialize(void)
{
	SafeRelease(select_button_);
	SafeRelease(select_button_frame_);
	SafeRelease(set_button_number_);
	SafeRelease(set_button_number_frame_);
}

//=============================================================================
// update
//=============================================================================
void KeyConfigOk::Update(void)
{
	select_button_->Update();
	select_button_frame_->Update();
	set_button_number_frame_->Update();
	set_button_number_->Update();
}

//=============================================================================
// draw
//=============================================================================
void KeyConfigOk::Draw(void)
{
	select_button_frame_->Draw();
	select_button_->Draw();
	set_button_number_frame_->Draw();
	set_button_number_->Draw();
}

//=============================================================================
// select
//=============================================================================
void KeyConfigOk::Select(bool is_select)
{
	if(is_select == true)
	{
		select_button_frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_001);
//		select_button_->__size(Option::EXPAND_MENU_SIZE);
	}
	else
	{
		select_button_frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_000);
//		select_button_->__size(Option::DEFAULT_MENU_SIZE);
	}
}

//=============================================================================
// set texture
//=============================================================================
void KeyConfigOk::__set_button_number_texture(INPUT_EVENT button)
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
}

//=============================================================================
// set alpha
//=============================================================================
void KeyConfigOk::SetAlpha(f32 alpha)
{
	select_button_->__color(D3DXCOLOR(1,1,1,alpha));
}


//---------------------------------- EOF --------------------------------------
