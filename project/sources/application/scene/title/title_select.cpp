//*****************************************************************************
//
// title select
//
// Author	: masato masuda
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "title_select.h"
#include "render/sprite.h"
#include "system/system.h"
#include "system/directx9/texture/texture.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 TitleSelect::DEFAULT_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f, DEFAULT_SCREEN_HEIGHT * 0.5f);
const f32 SIZE_SCALE = 0.85f;
const D3DXVECTOR2 TitleSelect::DEFAULT_SIZE = D3DXVECTOR2(256 * SIZE_SCALE, 64.0f * SIZE_SCALE);

//=============================================================================
// constructor
//=============================================================================
TitleSelect::TitleSelect(void)
	:sprite_(nullptr)
{
}

//=============================================================================
// destructor
//=============================================================================
TitleSelect::~TitleSelect(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool TitleSelect::Initialize(void)
{
	sprite_ = new Sprite();
	sprite_->Initialize();
	sprite_->__size(DEFAULT_SIZE);
	sprite_->__position(DEFAULT_POSITION);
	sprite_->__point(Sprite::POINT_CENTER);
	sprite_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_000);
	sprite_->SetParameter();
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void TitleSelect::Uninitialize(void)
{
	SafeRelease(sprite_);
}

//=============================================================================
// update
//=============================================================================
void TitleSelect::Update(void)
{
}

//=============================================================================
// draw
//=============================================================================
void TitleSelect::Draw(void)
{
	sprite_->Draw();
}

//=============================================================================
// __position
//=============================================================================
void TitleSelect::__position(const D3DXVECTOR2& position)
{
	sprite_->__position(position);
	sprite_->SetParameter();
}

//=============================================================================
// __texture_id
//=============================================================================
void TitleSelect::__texture_id(const Texture::TEXTURE_ID& texture_id)
{
	sprite_->__texture_id(texture_id);
	sprite_->SetParameter();
}

//=============================================================================
// __size
//=============================================================================
void TitleSelect::__size(const D3DXVECTOR2& size)
{
	sprite_->__size(size);
	sprite_->SetParameter();
}

//---------------------------------- EOF --------------------------------------
