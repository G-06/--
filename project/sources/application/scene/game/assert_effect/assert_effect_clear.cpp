//*****************************************************************************
//
// assert effect clear
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "assert_effect_clear.h"
#include "render/sprite.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const u32 AssertEffectClear::SRIDE_IN_FRAME = 30;
const u32 AssertEffectClear::STOP_FRAME = 60;
const u32 AssertEffectClear::SRIDE_OUT_FRAME = 30;

//=============================================================================
// constructor
//=============================================================================
AssertEffectClear::AssertEffectClear(void)
	:AssertEffect(TYPE_CLEAR)
	,sprite_(nullptr)
	,position_(0.0f,0.0f)
	,frame_count_(0)
	,is_stop_(false)
{
}

//=============================================================================
// destructor
//=============================================================================
AssertEffectClear::~AssertEffectClear(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool AssertEffectClear::Initialize(void)
{
	sprite_ = new Sprite();
	sprite_->Initialize();
	sprite_->__point(Sprite::POINT_CENTER);
	sprite_->__size(D3DXVECTOR2((f32)DEFAULT_SCREEN_WIDTH,200.0f));
	sprite_->SetParameter();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void AssertEffectClear::Uninitialize(void)
{
	SafeRelease(sprite_);
}

//=============================================================================
// update
//=============================================================================
void AssertEffectClear::Update(void)
{
	D3DXVECTOR2 vector;

	frame_count_++;

	if(frame_count_ <= SRIDE_IN_FRAME)
	{
		position_ = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 1.5f,DEFAULT_SCREEN_HEIGHT * 0.5f);
		purpose_position_ = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f,DEFAULT_SCREEN_HEIGHT * 0.5f);
		vector = purpose_position_ - position_;
		position_ = position_ + vector * 1.0f / (f32)SRIDE_IN_FRAME * (f32)frame_count_;
	}
	else if(frame_count_ <= SRIDE_IN_FRAME + STOP_FRAME)
	{
	}
	else if(frame_count_ <= SRIDE_IN_FRAME + STOP_FRAME + SRIDE_OUT_FRAME)
	{
		position_ = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f,DEFAULT_SCREEN_HEIGHT * 0.5f);
		purpose_position_ = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f,DEFAULT_SCREEN_HEIGHT * 0.2f);
		vector = purpose_position_ - position_;
		position_ = position_ + vector * 1.0f / (f32)SRIDE_OUT_FRAME * (f32)(frame_count_ - SRIDE_IN_FRAME - STOP_FRAME);
	}
	else
	{
		is_stop_ = true;
	}
}

//=============================================================================
// draw
//=============================================================================
void AssertEffectClear::Draw(void)
{
	if(is_assert_)
	{
		sprite_->__position(position_);
		sprite_->Draw();
	}
}

//---------------------------------- EOF --------------------------------------
