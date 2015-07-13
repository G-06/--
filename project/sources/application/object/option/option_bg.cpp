//*****************************************************************************
//
// option bg
//
// Author		: Ryotaro Arai
//				: masato masuda
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "option_bg.h"
#include "render/sprite.h"
#include "system/system.h"
#include "object/option/option_sprite_smooth.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 SIZE_SCALE = D3DXVECTOR2(1.1f,1.0f);
const D3DXVECTOR2 DEFAULT_SIZE = D3DXVECTOR2(853.0f * SIZE_SCALE.x, 700.0f * SIZE_SCALE.y);
const D3DXVECTOR2 DEFAULT_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f, DEFAULT_SCREEN_HEIGHT * 0.5f);

//=============================================================================
// constructor
//=============================================================================
OptionBg::OptionBg(void)
{
}

//=============================================================================
// destructor
//=============================================================================
OptionBg::~OptionBg(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool OptionBg::Initialize(void)
{
	sprite_ = new OptionSpriteSmooth();
	sprite_->Initialize();
	//sprite_->__size(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width()/3*2,(f32)GET_SYSTEM.__window()->__height()/5*4));
	//sprite_->__position(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width()/6,(f32)GET_SYSTEM.__window()->__height()/10));
	sprite_->__size(DEFAULT_SIZE);
	sprite_->__position(DEFAULT_POSITION);
	sprite_->__texture_id(Texture::TEXTURE_ID_OPTION_OPTION_WINDOW);
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void OptionBg::Uninitialize(void)
{
	SafeRelease(sprite_);
}

//=============================================================================
// update
//=============================================================================
void OptionBg::Update(void)
{
	sprite_->Update();
}

//=============================================================================
// draw
//=============================================================================
void OptionBg::Draw(void)
{
	sprite_->Draw();
}

//---------------------------------- EOF --------------------------------------
