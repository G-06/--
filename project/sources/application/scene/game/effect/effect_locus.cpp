//*****************************************************************************
//
// effect locus
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "effect_locus.h"
#include "render/sprite.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 EffectLocus::DOWN_SIZE = D3DXVECTOR2(128.0f/50.0f, 128.0f/50.0f);

//=============================================================================
// constructor
//=============================================================================
EffectLocus::EffectLocus(void)
	:Effect(TYPE_LOCUS)
	,sprite_(nullptr)
	,alpha_(0.5f)
	,is_free_(true)
{
}

//=============================================================================
// destructor
//=============================================================================
EffectLocus::~EffectLocus(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool EffectLocus::Initialize(void)
{
	sprite_ = new Sprite();
	SafeInitialize(sprite_);
	sprite_->__point(Sprite::POINT_CENTER);
	sprite_->__size(D3DXVECTOR2(128.0f,128.0f));
	sprite_->__texture_id(Texture::TEXTURE_ID_NYAS_LIGHT);
	sprite_->__division_width(6);
	sprite_->__index(0);
	sprite_->SetParameter();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void EffectLocus::Uninitialize(void)
{
	SafeRelease(sprite_);
}

//=============================================================================
// update
//=============================================================================
void EffectLocus::Update(void)
{
	alpha_ -= 0.01f;
	if(alpha_ <= 0.4)
	{
		alpha_ -= 0.02f;
		sprite_->__size(sprite_->__size() - DOWN_SIZE - DOWN_SIZE);
	}

	if(alpha_ <= 0)
	{
		is_death_ = true;
	}
	sprite_->__size(sprite_->__size() - DOWN_SIZE);
	sprite_->__color(D3DXCOLOR(255,255,255,alpha_));
	sprite_->SetParameter();
}

//=============================================================================
// draw
//=============================================================================
void EffectLocus::Draw(void)
{
	sprite_->__position(position_ - offset_position_);
	sprite_->Draw();
}

//=============================================================================
// start
//=============================================================================
void EffectLocus::Start(void)
{
	alpha_ = 0.5f;

	sprite_->__color(D3DXCOLOR(255,255,255,alpha_));
	sprite_->__size(D3DXVECTOR2(128.0f,128.0f));
	sprite_->SetParameter();
	is_death_ = false;
	is_free_ = false;
}

//---------------------------------- EOF --------------------------------------
