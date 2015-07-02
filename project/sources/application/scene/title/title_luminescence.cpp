//*****************************************************************************
//
// title luminescence
//
// Author	: masato masuda
//
// ”­Œõ‚µ‚Ä‚é‚â‚Â
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "title_luminescence.h"
#include "render/sprite.h"
#include "system/system.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
//const D3DXVECTOR2 Titleluminescence::DEFAULT_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f, DEFAULT_SCREEN_HEIGHT * 0.5f);
const D3DXVECTOR2 Titleluminescence::DEFAULT_POSITION = D3DXVECTOR2(0.0f, 0.0f);
const D3DXVECTOR2 Titleluminescence::DEFAULT_SIZE = D3DXVECTOR2((f32)DEFAULT_SCREEN_WIDTH, 360.0f);
const f32 DEFAULT_ALPHA_SPEED = -0.0075f;

//=============================================================================
// constructor
//=============================================================================
Titleluminescence::Titleluminescence(void)
	:sprite_(nullptr)
	,alpha_speed_(DEFAULT_ALPHA_SPEED)
	,alpha_(1.0f)
{
}

//=============================================================================
// destructor
//=============================================================================
Titleluminescence::~Titleluminescence(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool Titleluminescence::Initialize(void)
{
	sprite_ = new Sprite();
	sprite_->Initialize();
	sprite_->__size(DEFAULT_SIZE);
	sprite_->__position(DEFAULT_POSITION);
	sprite_->__point(Sprite::POINT_LEFT_UP);
	sprite_->__texture_id(Texture::TEXTURE_ID_TITLE_LUMINESCENCE);
	sprite_->SetParameter();
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void Titleluminescence::Uninitialize(void)
{
	SafeRelease(sprite_);
}

//=============================================================================
// update
//=============================================================================
void Titleluminescence::Update(void)
{
}

//=============================================================================
// draw
//=============================================================================
void Titleluminescence::Draw(void)
{
	sprite_->Draw();
}

//=============================================================================
// __color
//=============================================================================
void Titleluminescence::__color(const D3DXCOLOR& color)
{
	sprite_->__color(color);
	sprite_->SetParameter();
}

//=============================================================================
// __color
//=============================================================================
const D3DXCOLOR Titleluminescence::__color(void)
{
	return (D3DXCOLOR)sprite_->__color();
}

//=============================================================================
// ResetAlphaSpeed
//=============================================================================
void Titleluminescence::ResetAlphaSpeed(void)
{
	alpha_speed_ = DEFAULT_ALPHA_SPEED;
}

//=============================================================================
// __texture_id
//=============================================================================
void Titleluminescence::__texture_id(const Texture::TEXTURE_ID& texture_id)
{
	sprite_->__texture_id(texture_id);
	sprite_->SetParameter();
}

//---------------------------------- EOF --------------------------------------
