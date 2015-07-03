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
#include "system/system.h"

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
	,alpha_(0.1f)
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
	sprite_->__texture_id(Texture::TEXTURE_ID_EFFECT_LOCUS);
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
	alpha_ = 0.0f;

	if(sprite_->__size() <= D3DXVECTOR2(128.0f/50*20, 128.0f/50*20))
	{
		sprite_->__size(sprite_->__size() - DOWN_SIZE - DOWN_SIZE);
		alpha_+= -0.004f;
	}

	if(sprite_->__size().x <= 0.0f && sprite_->__size().y <= 0.0f )
	{
		is_death_ = true;
	}
	sprite_->__size(sprite_->__size() - DOWN_SIZE);
	alpha_+= -0.002f;
	sprite_->__color(D3DXCOLOR(255,255,255,alpha_));
	sprite_->SetParameter();
}

//=============================================================================
// draw
//=============================================================================
void EffectLocus::Draw(void)
{
	LPDIRECT3DDEVICE9 device;
	device = GET_DIRECTX9_DEVICE;

	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	sprite_->__position(position_ - offset_position_);
	sprite_->Draw();
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
}

//=============================================================================
// start
//=============================================================================
void EffectLocus::Start(void)
{
	alpha_ = 0.1f;

	sprite_->__color(D3DXCOLOR(255,255,255,0.1f));
	sprite_->__size(D3DXVECTOR2(128.0f,128.0f));
	sprite_->SetParameter();
	is_death_ = false;
	is_free_ = false;
}

//---------------------------------- EOF --------------------------------------
