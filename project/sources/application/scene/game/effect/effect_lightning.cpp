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
const Animation::DATA EffectLightning::LIGHTNING_EFFECT[13] =
{
	Animation::DATA(4,1,0),
	Animation::DATA(4,2,1),
	Animation::DATA(4,3,2),
	Animation::DATA(4,4,3),
	Animation::DATA(4,5,4),
	Animation::DATA(4,6,5),
	Animation::DATA(4,7,6),
	Animation::DATA(4,8,7),
	Animation::DATA(4,9,8),
	Animation::DATA(4,10,9),
	Animation::DATA(4,11,10),
	Animation::DATA(4,12,11),
	Animation::DATA(4,0,12)
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
	animation_->Add(&LIGHTNING_EFFECT[0], sizeof(Animation::DATA)*13);

	sprite_ = new Sprite();
	SafeInitialize(sprite_);
	sprite_->__point(Sprite::POINT_CENTER);
	sprite_->__size(D3DXVECTOR2(128.0f,128.0f));
	sprite_->__texture_id(Texture::TEXTURE_ID_GAME_STRING_CHECK_POINT);
	sprite_->__division_height(1);
	sprite_->__division_width(13);
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

	if(frame_count_ > 52)
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
