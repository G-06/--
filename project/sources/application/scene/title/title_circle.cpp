//*****************************************************************************
//
// title circle
//
// Author	: masato masuda
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "title_circle.h"
#include "render/sprite.h"
#include "system/system.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 TitleCircle::DEFAULT_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f, DEFAULT_SCREEN_HEIGHT * 0.5f);
const f32 circle_scale = 0.4f;
const D3DXVECTOR2 TitleCircle::DEFAULT_SIZE = D3DXVECTOR2(2147.0f * circle_scale, 2147.0f * circle_scale);

//=============================================================================
// constructor
//=============================================================================
TitleCircle::TitleCircle(void)
	:sprite_(nullptr)
{
}

//=============================================================================
// destructor
//=============================================================================
TitleCircle::~TitleCircle(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool TitleCircle::Initialize(void)
{
	sprite_ = new Sprite();
	sprite_->Initialize();
	sprite_->__size(DEFAULT_SIZE);
	sprite_->__position(DEFAULT_POSITION);
	sprite_->__point(Sprite::POINT_CENTER);
	sprite_->__texture_id(Texture::TEXTURE_ID_TITLE_CIRCLE);
	sprite_->SetParameter();
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void TitleCircle::Uninitialize(void)
{
	SafeRelease(sprite_);
}

//=============================================================================
// update
//=============================================================================
void TitleCircle::Update(void)
{
}

//=============================================================================
// draw
//=============================================================================
void TitleCircle::Draw(void)
{
	sprite_->Draw();
}

//=============================================================================
// AddRotation
//=============================================================================
void TitleCircle::AddRotation(const f32 rotation)
{
	f32 old_rotation = sprite_->__rotation();
	f32 temp_rotation = old_rotation + rotation;

	// normalize
	if( temp_rotation > D3DX_PI ){
		temp_rotation -= ( 2.0f * D3DX_PI );
	}
	if( temp_rotation < -(D3DX_PI) ){
		temp_rotation += ( 2.0f * D3DX_PI );
	}

	sprite_->__rotation(temp_rotation);
}

//=============================================================================
// __texture_id
//=============================================================================
void TitleCircle::__texture_id(const Texture::TEXTURE_ID& texture_id)
{
	sprite_->__texture_id(texture_id);
	sprite_->SetParameter();
}

//---------------------------------- EOF --------------------------------------
