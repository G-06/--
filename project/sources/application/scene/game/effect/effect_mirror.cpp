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
#include "system/system.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const Animation::DATA EffectMirror::MIRROR_EFFECT[EffectMirror::MIRROR_EFFECT_PATTERN] =
{
	Animation::DATA(3,1,0),
	Animation::DATA(3,2,1),
	Animation::DATA(3,3,2),
	Animation::DATA(3,4,3),
	Animation::DATA(3,5,4),
	Animation::DATA(3,6,5),
	Animation::DATA(3,7,6),
	Animation::DATA(3,8,7),
	Animation::DATA(3,9,8),
	Animation::DATA(3,10,9),
	Animation::DATA(3,0,10),
};


//=============================================================================
// constructor
//=============================================================================
EffectMirror::EffectMirror(void)
	:Effect(TYPE_MIRROR)
	,sprite_(nullptr)
	,frame_count_(0)
	,is_free_(true)
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

	sprite_ = new Sprite();
	SafeInitialize(sprite_);
	sprite_->__point(Sprite::POINT_CENTER);
	sprite_->__size(D3DXVECTOR2(256.0f,256.0f));
	sprite_->__texture_id(Texture::TEXTURE_ID_EFFECT_MIRROR);
	sprite_->__division_width(4);
	sprite_->__division_height(3);
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

	if(frame_count_ > MIRROR_FRAME)
	{
		is_death_ = true;
		is_free_ = true;
		animation_->Stop();
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

//=============================================================================
// start
//=============================================================================
void EffectMirror::Start(void)
{
	frame_count_ = 0;
	is_death_ = false;
	is_free_ = false;
	animation_->Start(0);
	sprite_->__index(0);
}

//---------------------------------- EOF --------------------------------------
