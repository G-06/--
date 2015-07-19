//*****************************************************************************
//
// keyconfig logo
//
// Author		: Ryotaro Arai
//				: masato masuda
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "keyconfig_logo.h"
#include "render/sprite.h"
#include "system/system.h"
#include "object/option/option_sprite_smooth.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
//const D3DXVECTOR2 DEFAULT_SIZE = Option::DEFAULT_MENU_SIZE;
const f32 SIZE_SCALE = 0.95f;
const D3DXVECTOR2 DEFAULT_SIZE = D3DXVECTOR2(256.0f * SIZE_SCALE, 64.0f * SIZE_SCALE);
const D3DXVECTOR2 DEFAULT_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f - 275, 350.f);

//=============================================================================
// constructor
//=============================================================================
KeyconfigLogo::KeyconfigLogo(void)
	:sprite_(NULL)
{
}

//=============================================================================
// destructor
//=============================================================================
KeyconfigLogo::~KeyconfigLogo(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool KeyconfigLogo::Initialize(void)
{
	sprite_ = new OptionSpriteSmooth();
	sprite_->Initialize();
	sprite_->__size(DEFAULT_SIZE);
	sprite_->__position(DEFAULT_POSITION);
	sprite_->__texture_id(Texture::TEXTURE_ID_OPTION_STRING_KEY_CONFIG);
	sprite_->__point(Sprite::POINT_CENTER);

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void KeyconfigLogo::Uninitialize(void)
{
	SafeRelease(sprite_);
}

//=============================================================================
// update
//=============================================================================
void KeyconfigLogo::Update(void)
{
	sprite_->Update();
}

//=============================================================================
// draw
//=============================================================================
void KeyconfigLogo::Draw(void)
{
	sprite_->Draw();
}

//=============================================================================
// __position
//=============================================================================
void KeyconfigLogo::__position(const D3DXVECTOR2 position)
{
	sprite_->__position(position);
}

//---------------------------------- EOF --------------------------------------
