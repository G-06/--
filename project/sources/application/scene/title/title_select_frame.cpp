//*****************************************************************************
//
// title select_frame
//
// Author	: masato masuda
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "title_select_frame.h"
#include "render/sprite.h"
#include "system/system.h"
#include "system/directx9/texture/texture.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 TitleSelectFrame::DEFAULT_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f, DEFAULT_SCREEN_HEIGHT * 0.5f);
const D3DXVECTOR2 TitleSelectFrame::DEFAULT_SIZE = D3DXVECTOR2(324.0f,71.0f);

//=============================================================================
// constructor
//=============================================================================
TitleSelectFrame::TitleSelectFrame(void)
	:sprite_(nullptr)
{
}

//=============================================================================
// destructor
//=============================================================================
TitleSelectFrame::~TitleSelectFrame(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool TitleSelectFrame::Initialize(void)
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
void TitleSelectFrame::Uninitialize(void)
{
	SafeRelease(sprite_);
}

//=============================================================================
// update
//=============================================================================
void TitleSelectFrame::Update(void)
{
}

//=============================================================================
// draw
//=============================================================================
void TitleSelectFrame::Draw(void)
{
	sprite_->Draw();
}

//=============================================================================
// __position
//=============================================================================
void TitleSelectFrame::__position(const D3DXVECTOR2& position)
{
	sprite_->__position(position);
}

//=============================================================================
// __texture_id
//=============================================================================
void TitleSelectFrame::__texture_id(const Texture::TEXTURE_ID& texture_id)
{
	sprite_->__texture_id(texture_id);
}


//---------------------------------- EOF --------------------------------------
