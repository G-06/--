//*****************************************************************************
//
// key config cancel
//
// Author		: Ryotaro Arai
//				: masato masuda
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "key_config_cancel.h"
#include "render/sprite.h"
#include "../option.h"
#include "object/option/option_sprite_smooth.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
// string
const D3DXVECTOR2 DEFAULT_SIZE = Option::DEFAULT_MENU_SIZE;
const D3DXVECTOR2 DEFAULT_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f - 250, 460.0f);
// number
const D3DXVECTOR2 DEFAULT_NUM_SIZE = D3DXVECTOR2(DEFAULT_SIZE.y, DEFAULT_SIZE.y);
const D3DXVECTOR2 DEFAULT_NUM_POSITION = D3DXVECTOR2(DEFAULT_POSITION.x + 300.0f, DEFAULT_POSITION.y);

//=============================================================================
// constructor
//=============================================================================
KeyConfigCancel::KeyConfigCancel(void)
	:cancel_button_(NULL)
	,cancel_button_frame_(NULL)
	,set_button_number_(NULL)
	,set_button_number_frame_(NULL)
	,current_key_event_(NULL)
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
	cancel_button_ = new OptionSpriteSmooth();
	cancel_button_->Initialize();
	cancel_button_->__size(DEFAULT_SIZE);
	cancel_button_->__position(DEFAULT_POSITION);
	cancel_button_->__texture_id(Texture::TEXTURE_ID_OPTION_STRING_OP_CANCEL);

	cancel_button_frame_ = new OptionSpriteSmooth();
	cancel_button_frame_->Initialize();
	cancel_button_frame_->__size(DEFAULT_SIZE);
	cancel_button_frame_->__position(DEFAULT_POSITION);
	cancel_button_frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_000);

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
void KeyConfigCancel::Uninitialize(void)
{
	SafeRelease(cancel_button_);
	SafeRelease(cancel_button_frame_);
	SafeRelease(set_button_number_);
	SafeRelease(set_button_number_frame_);
}

//=============================================================================
// update
//=============================================================================
void KeyConfigCancel::Update(void)
{
	cancel_button_->Update();
	cancel_button_frame_->Update();
	set_button_number_->Update();
	set_button_number_frame_->Update();
}

//=============================================================================
// draw
//=============================================================================
void KeyConfigCancel::Draw(void)
{
	cancel_button_frame_->Draw();
	cancel_button_->Draw();
	set_button_number_frame_->Draw();
	set_button_number_->Draw();
}

//=============================================================================
// select
//=============================================================================
void KeyConfigCancel::Select(bool is_select)
{
	if(is_select == true)
	{
		cancel_button_frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_001);
	}
	else
	{
		cancel_button_frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_000);
	}
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

		case INPUT_EVENT_PAD_14:
			set_button_number_->__texture_id(Texture::TEXTURE_ID_OPTION_KEY_14);
			break;

		case INPUT_EVENT_PAD_15:
			set_button_number_->__texture_id(Texture::TEXTURE_ID_OPTION_KEY_15);
			break;

		default :
			set_button_number_->__texture_id(Texture::TEXTURE_ID_DOT);
			break;
	}
}


//=============================================================================
// set alpha
//=============================================================================
void KeyConfigCancel::SetAlpha(f32 alpha)
{
	set_button_number_->__color(D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha));
}

//=============================================================================
// __position
//=============================================================================
void KeyConfigCancel::__position(const D3DXVECTOR2 position, const float offset_x)
{
	cancel_button_->__position(position);
	cancel_button_frame_->__position(position);
	set_button_number_frame_->__position(D3DXVECTOR2(position.x + offset_x, position.y));
	set_button_number_->__position(D3DXVECTOR2(position.x + offset_x, position.y));
}

//=============================================================================
// __texture_id
//=============================================================================
void KeyConfigCancel::__texture_id_frame(const Texture::TEXTURE_ID& texture_id)
{
	cancel_button_frame_->__texture_id(texture_id);
}

//---------------------------------- EOF --------------------------------------
