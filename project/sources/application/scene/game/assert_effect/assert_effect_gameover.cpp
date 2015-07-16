//*****************************************************************************
//
// assert effect gameover
//
// Author		: taichi kitazawa
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "assert_effect_gameover.h"
#include "render/sprite.h"
#include "system/system.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const f32 AssertEffectGameover::FADE_IN_FRAME = 40;
const u32 AssertEffectGameover::SRIDE_IN_FRAME = 30;
const u32 AssertEffectGameover::STOP_FRAME = 90;
const u32 AssertEffectGameover::SRIDE_OUT_FRAME = 30;
const f32 AssertEffectGameover::MAX_ALPHA = 0.7f;

//=============================================================================
// constructor
//=============================================================================
AssertEffectGameover::AssertEffectGameover(void)
	:AssertEffect(TYPE_START)
	,sprite_(nullptr)
	,position_(0.0f,0.0f)
	,frame_count_(0)
{
}

//=============================================================================
// destructor
//=============================================================================
AssertEffectGameover::~AssertEffectGameover(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool AssertEffectGameover::Initialize(void)
{
	sprite_ = new Sprite();
	sprite_->Initialize();
	sprite_->__point(Sprite::POINT_CENTER);
	sprite_->__size(D3DXVECTOR2((f32)DEFAULT_SCREEN_WIDTH,200.0f));
	sprite_->__texture_id(Texture::TEXTURE_ID_GAME_STRING_START);
	position_=D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width()*2.0f,(f32)GET_SYSTEM.__window()->__width()*2.0f);
	sprite_->__position(position_);

	sprite_->SetParameter();


	alpha_ = 0.0f;

	fade_ = new Sprite();
	fade_->Initialize();
	fade_->__position(D3DXVECTOR2(0.0f,0.0f));
	fade_->__size(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width(),(f32)GET_SYSTEM.__window()->__height()));
	fade_->__color(D3DXCOLOR(0.0f,0.0f,0.0f,alpha_));
	fade_->SetParameter();

	is_stop_ = false;

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void AssertEffectGameover::Uninitialize(void)
{
	SafeRelease(sprite_);
	SafeRelease(fade_);
}

//=============================================================================
// update
//=============================================================================
void AssertEffectGameover::Update(void)
{
	D3DXVECTOR2 vector;

	frame_count_++;

	if(frame_count_ <=FADE_IN_FRAME)
	{
		alpha_ += (MAX_ALPHA/FADE_IN_FRAME);
		fade_->__color(D3DXCOLOR(0.0f,0.0f,0.0f,alpha_));
		fade_->SetParameter();
	}
	else if(frame_count_ <= FADE_IN_FRAME + SRIDE_IN_FRAME)
	{
		position_ = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 1.5f,DEFAULT_SCREEN_HEIGHT * 0.5f);
		purpose_position_ = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f,DEFAULT_SCREEN_HEIGHT * 0.5f);
		vector = purpose_position_ - position_;
		position_ = position_ + vector * 1.0f / (f32)SRIDE_IN_FRAME * (f32)(frame_count_ - FADE_IN_FRAME);
	}
	else if(frame_count_ <= FADE_IN_FRAME + SRIDE_IN_FRAME + STOP_FRAME)
	{
	}
	else
	{
		is_stop_ = true;
	}
}

//=============================================================================
// draw
//=============================================================================
void AssertEffectGameover::Draw(void)
{
	if(is_assert_)
	{
		fade_->Draw();
		sprite_->__position(position_);
		sprite_->Draw();
	}
}

//---------------------------------- EOF --------------------------------------
