//*****************************************************************************
//
// volume logo
//
// Author		: Ryotaro Arai
//				: masato masuda
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "volume_logo.h"
#include "render/sprite.h"
#include "system/system.h"
#include "../option.h"
#include "object/option/option_sprite_smooth.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
//const D3DXVECTOR2 DEFAULT_SIZE = Option::DEFAULT_MENU_SIZE;
const f32 SIZE_SCALE = 0.8f;
const D3DXVECTOR2 DEFAULT_SIZE = D3DXVECTOR2(256.0f * SIZE_SCALE, 64.0f * SIZE_SCALE);
const D3DXVECTOR2 DEFAULT_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f - 320.0f, 140.f);

//=============================================================================
// constructor
//=============================================================================
VolumeLogo::VolumeLogo(void)
	:sprite_(NULL)
{
}

//=============================================================================
// destructor
//=============================================================================
VolumeLogo::~VolumeLogo(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool VolumeLogo::Initialize(void)
{
	sprite_ = new OptionSpriteSmooth();
	sprite_->Initialize();
	sprite_->__size(DEFAULT_SIZE);
	sprite_->__position(DEFAULT_POSITION);
	sprite_->__point(Sprite::POINT_CENTER);
	sprite_->__texture_id(Texture::TEXTURE_ID_OPTION_STRING_SOUND_CONFIG);

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void VolumeLogo::Uninitialize(void)
{
	SafeRelease(sprite_);
}

//=============================================================================
// update
//=============================================================================
void VolumeLogo::Update(void)
{
	sprite_->Update();
}

//=============================================================================
// draw
//=============================================================================
void VolumeLogo::Draw(void)
{
	sprite_->Draw();
}

//=============================================================================
// __position
//=============================================================================
void VolumeLogo::__position(const D3DXVECTOR2 position)
{
	sprite_->__position(position);
}

//---------------------------------- EOF --------------------------------------
