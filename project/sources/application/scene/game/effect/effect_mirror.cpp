//*****************************************************************************
//
// effect mirror
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "effect_mirror.h"
#include "render/sprite.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const Animation::DATA EffectMirror::MIRROR_EFFECT[EffectMirror::MIRROR_EFFECT_PATTERN] =
{
	Animation::DATA(2,1,0),
	Animation::DATA(2,2,1),
	Animation::DATA(2,3,2),
	Animation::DATA(2,4,3),
	Animation::DATA(2,5,4),
	Animation::DATA(2,6,5),
	Animation::DATA(2,7,6),
	Animation::DATA(2,8,7),
	Animation::DATA(2,9,8),
	Animation::DATA(2,10,9),
	Animation::DATA(2,11,10),
	Animation::DATA(2,0,11)
};


//=============================================================================
// constructor
//=============================================================================
EffectMirror::EffectMirror(void)
	:Effect(TYPE_MIRROR)
	,sprite_(nullptr)
	,frame_count_(0)
{
}

//=============================================================================
// destructor
//=============================================================================
EffectMirror::~EffectMirror(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool EffectMirror::Initialize(void)
{
	animation_ = new Animation();
	animation_->Add(&MIRROR_EFFECT[0], sizeof(Animation::DATA)*EffectMirror::MIRROR_EFFECT_PATTERN);
	animation_->Start(0);

	sprite_ = new Sprite();
	SafeInitialize(sprite_);
	sprite_->__point(Sprite::POINT_CENTER);
	sprite_->__size(D3DXVECTOR2(256.0f,256.0f));
	sprite_->__texture_id(Texture::TEXTURE_ID_EFFECT_MIRROR);
	sprite_->__division_width(EffectMirror::MIRROR_EFFECT_PATTERN);
	sprite_->__index(0);
	sprite_->SetParameter();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void EffectMirror::Uninitialize(void)
{
	SafeRelease(sprite_);
	SafeRelease(animation_);
}

//=============================================================================
// update
//=============================================================================
void EffectMirror::Update(void)
{
	frame_count_++;

	if(frame_count_ > 24)
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
void EffectMirror::Draw(void)
{
	sprite_->__position(position_ - offset_position_);
	sprite_->Draw();
}

//---------------------------------- EOF --------------------------------------
