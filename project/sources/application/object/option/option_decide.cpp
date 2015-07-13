//*****************************************************************************
//
// option decide
//
// Author	: masato masuda
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "option_decide.h"
#include "render/sprite.h"
#include "../option.h"
#include "object/option/option_sprite_smooth.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
// string
const D3DXVECTOR2 DEFAULT_SIZE = Option::DEFAULT_MENU_SIZE;
const D3DXVECTOR2 DEFAULT_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f, 410.0f);
// number
const D3DXVECTOR2 DEFAULT_NUM_SIZE = D3DXVECTOR2(0.0f,0.0f);
const D3DXVECTOR2 DEFAULT_NUM_POSITION = D3DXVECTOR2(0.0f,0.0f);


//=============================================================================
// constructor
//=============================================================================
OptionDecide::OptionDecide(void)
	:sprite_(NULL)
	,sprite_frame_(NULL)
{
}

//=============================================================================
// destructor
//=============================================================================
OptionDecide::~OptionDecide(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool OptionDecide::Initialize(void)
{
	sprite_ = new OptionSpriteSmooth();
	sprite_->Initialize();
	sprite_->__size(DEFAULT_SIZE);
	sprite_->__position(DEFAULT_POSITION);
	sprite_->__texture_id(Texture::TEXTURE_ID_OPTION_STRING_OP_DECIDE);

	sprite_frame_ = new OptionSpriteSmooth();
	sprite_frame_->Initialize();
	sprite_frame_->__size(DEFAULT_SIZE);
	sprite_frame_->__position(DEFAULT_POSITION);
	sprite_frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_000);

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void OptionDecide::Uninitialize(void)
{
	SafeRelease(sprite_);
	SafeRelease(sprite_frame_);
}

//=============================================================================
// update
//=============================================================================
void OptionDecide::Update(void)
{
	sprite_->Update();
	sprite_frame_->Update();
}

//=============================================================================
// draw
//=============================================================================
void OptionDecide::Draw(void)
{
	sprite_frame_->Draw();
	sprite_->Draw();
}

//=============================================================================
// select
//=============================================================================
void OptionDecide::Select(bool is_select)
{
	if(is_select == true)
	{
		sprite_frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_001);
	}
	else
	{
		sprite_frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_000);
	}
}


//=============================================================================
// __position
//=============================================================================
void OptionDecide::__position(const D3DXVECTOR2 position, const float offset_x)
{
	sprite_frame_->__position(position);
	sprite_->__position(position);
}

//=============================================================================
// __texture_id
//=============================================================================
void OptionDecide::__texture_id_frame(const Texture::TEXTURE_ID& texture_id)
{
	sprite_frame_->__texture_id(texture_id);
}


//---------------------------------- EOF --------------------------------------
