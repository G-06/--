//*****************************************************************************
//
// effect lightning
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "effect_lightning.h"
#include "render/sprite.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const Animation::DATA EffectLightning::LIGHTNING_EFFECT[EffectLightning::LIGHTNING_EFFECT_PATTERN] =
{
	Animation::DATA(3,1,0),
	Animation::DATA(3,2,1),
	Animation::DATA(3,3,2),
	Animation::DATA(3,4,3),
	Animation::DATA(3,5,4),
	Animation::DATA(3,6,5),
	Animation::DATA(3,7,6),
	Animation::DATA(3,0,7),
};


//=============================================================================
// constructor
//=============================================================================
EffectLightning::EffectLightning(void)
	:Effect(TYPE_LIGHTNING)
	,sprite_(nullptr)
	,frame_count_(0)
{
}

//=============================================================================
// destructor
//=============================================================================
EffectLightning::~EffectLightning(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool EffectLightning::Initialize(void)
{
	animation_ = new Animation();
	animation_->Add(&LIGHTNING_EFFECT[0], sizeof(Animation::DATA)*EffectLightning::LIGHTNING_EFFECT_PATTERN);
	animation_->Start(0);

	sprite_ = new Sprite();
	SafeInitialize(sprite_);
	sprite_->__point(Sprite::POINT_CENTER);
	sprite_->__size(D3DXVECTOR2(384.0f,384.0f));
	sprite_->__texture_id(Texture::TEXTURE_ID_EFFECT_LIGHTNING);
	sprite_->__division_width(EffectLightning::LIGHTNING_EFFECT_PATTERN);
	sprite_->__index(0);
	sprite_->SetParameter();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void EffectLightning::Uninitialize(void)
{
	SafeRelease(sprite_);
	SafeRelease(animation_);
}

//=============================================================================
// update
//=============================================================================
void EffectLightning::Update(void)
{
	frame_count_++;

	if(frame_count_ > 23)
	{
		is_death_ = true;
	}

	animation_->Update();
	sprite_->__index(animation_->__current_index());
	sprite_->SetParameter();
}

//=============================================================================
// draw
//=============================================================================
void EffectLightning::Draw(void)
{
	sprite_->__position(position_ - offset_position_);
	sprite_->Draw();
}

//---------------------------------- EOF --------------------------------------
