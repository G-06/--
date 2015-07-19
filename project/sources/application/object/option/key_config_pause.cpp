//*****************************************************************************
//
// key config pause
//
// Author		: Ryotaro Arai
//				: masato masuda
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "key_config_pause.h"
#include "render/sprite.h"
#include "../option.h"
#include "object/option/option_sprite_smooth.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
// string
const D3DXVECTOR2 DEFAULT_SIZE = Option::DEFAULT_MENU_SIZE;
const D3DXVECTOR2 DEFAULT_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f - 250, 525.0f);
// number
const D3DXVECTOR2 DEFAULT_NUM_SIZE = D3DXVECTOR2(Option::DEFAULT_MENU_NUM_SIZE.y, Option::DEFAULT_MENU_NUM_SIZE.y);
const D3DXVECTOR2 DEFAULT_NUM_FRAME_SIZE = D3DXVECTOR2(Option::DEFAULT_MENU_FRAME_SIZE.y, Option::DEFAULT_MENU_FRAME_SIZE.y);
const D3DXVECTOR2 DEFAULT_NUM_POSITION = D3DXVECTOR2(DEFAULT_POSITION.x + 300.0f, DEFAULT_POSITION.y);

//=============================================================================
// constructor
//=============================================================================
KeyConfigPause::KeyConfigPause(void)
	:pause_button_(NULL)
	,pause_button_frame_(NULL)
	,set_button_number_(NULL)
	,set_button_number_frame_(NULL)
	,current_key_event_(NULL)
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
	pause_button_ = new OptionSpriteSmooth();
	pause_button_->Initialize();
	pause_button_->__size(DEFAULT_SIZE);
	pause_button_->__position(DEFAULT_POSITION);
	pause_button_->__texture_id(Texture::TEXTURE_ID_OPTION_STRING_OP_PAUSE);

	pause_button_frame_ = new OptionSpriteSmooth();
	pause_button_frame_->Initialize();
	pause_button_frame_->__size(Option::DEFAULT_MENU_FRAME_SIZE);
	pause_button_frame_->__position(DEFAULT_POSITION);
	pause_button_frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_000);

	set_button_number_ = new OptionSpriteSmooth();
	set_button_number_->Initialize();
	set_button_number_->__size(DEFAULT_NUM_SIZE);
	set_button_number_->__position(DEFAULT_NUM_POSITION);
	set_button_number_->__texture_id(Texture::TEXTURE_ID_OPTION_KEY_01);

	set_button_number_frame_ = new OptionSpriteSmooth();
	set_button_number_frame_->Initialize();
	set_button_number_frame_->__size(DEFAULT_NUM_FRAME_SIZE);
	set_button_number_frame_->__position(DEFAULT_NUM_POSITION);
	set_button_number_frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_000);

	current_key_event_ = NULL;

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void KeyConfigPause::Uninitialize(void)
{
	SafeRelease(pause_button_);
	SafeRelease(pause_button_frame_);
	SafeRelease(set_button_number_);
	SafeRelease(set_button_number_frame_);
}

//=============================================================================
// update
//=============================================================================
void KeyConfigPause::Update(void)
{
	pause_button_->Update();
	pause_button_frame_->Update();
	set_button_number_->Update();
	set_button_number_frame_->Update();
}

//=============================================================================
// draw
//=============================================================================
void KeyConfigPause::Draw(void)
{
	pause_button_frame_->Draw();
	pause_button_->Draw();
	set_button_number_frame_->Draw();
	set_button_number_->Draw();
}

//=============================================================================
// select
//=============================================================================
void KeyConfigPause::Select(bool is_select)
{
	if(is_select == true)
	{
		pause_button_frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_001);
	}
	else
	{
		pause_button_frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_000);
	}
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
void KeyConfigPause::SetAlpha(f32 alpha)
{
	set_button_number_->__color(D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha));
}

//=============================================================================
// __position
//=============================================================================
void KeyConfigPause::__position(const D3DXVECTOR2 position, const float offset_x)
{
	pause_button_->__position(position);
	pause_button_frame_->__position(position);
	set_button_number_frame_->__position(D3DXVECTOR2(position.x + offset_x, position.y));
	set_button_number_->__position(D3DXVECTOR2(position.x + offset_x, position.y));
}

//=============================================================================
// __texture_id
//=============================================================================
void KeyConfigPause::__texture_id_frame(const Texture::TEXTURE_ID& texture_id)
{
	pause_button_frame_->__texture_id(texture_id);
}

//---------------------------------- EOF --------------------------------------
