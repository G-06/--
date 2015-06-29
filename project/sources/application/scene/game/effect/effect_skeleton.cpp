//*****************************************************************************
//
// effect skeleton
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "effect_skeleton.h"
#include "render/sprite.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const Animation::DATA EffectSkeleton::SKELETON_EFFECT[EffectSkeleton::SKELETON_EFFECT_PATTERN] =
{
	Animation::DATA(3,1,0),
	Animation::DATA(3,2,1),
	Animation::DATA(3,3,2),
	Animation::DATA(3,4,3),
	Animation::DATA(3,5,4),
	Animation::DATA(3,6,5),
	Animation::DATA(3,7,6),
	Animation::DATA(3,0,7)
};


//=============================================================================
// constructor
//=============================================================================
EffectSkeleton::EffectSkeleton(void)
	:Effect(TYPE_SKELETON)
	,sprite_(nullptr)
	,frame_count_(0)
{
}

//=============================================================================
// destructor
//=============================================================================
EffectSkeleton::~EffectSkeleton(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool EffectSkeleton::Initialize(void)
{
	animation_ = new Animation();
	animation_->Add(&SKELETON_EFFECT[0], sizeof(Animation::DATA)*EffectSkeleton::SKELETON_EFFECT_PATTERN);
	animation_->Start(0);

	sprite_ = new Sprite();
	SafeInitialize(sprite_);
	sprite_->__point(Sprite::POINT_CENTER);
	sprite_->__size(D3DXVECTOR2(256.0f,256.0f));
	sprite_->__texture_id(Texture::TEXTURE_ID_EFFECT_SKELETON);
	sprite_->__division_width(EffectSkeleton::SKELETON_EFFECT_PATTERN);
	sprite_->__index(0);
	sprite_->SetParameter();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void EffectSkeleton::Uninitialize(void)
{
	SafeRelease(sprite_);
	SafeRelease(animation_);
}

//=============================================================================
// update
//=============================================================================
void EffectSkeleton::Update(void)
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
void EffectSkeleton::Draw(void)
{
	sprite_->__position(position_ - offset_position_);
	sprite_->Draw();
}

//---------------------------------- EOF --------------------------------------
