//*****************************************************************************
//
// assert effect start
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "assert_effect_start.h"
#include "render/sprite.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const u32 AssertEffectStart::SRIDE_IN_FRAME = 30;
const u32 AssertEffectStart::STOP_FRAME = 90;
const u32 AssertEffectStart::SRIDE_OUT_FRAME = 30;

const D3DXVECTOR2 SPRITE_SIZE = D3DXVECTOR2(1028.0f,256.0f);
const D3DXVECTOR2 SPRITE_BACK_SIZE = D3DXVECTOR2(1280.0f,300.0f);
const f32 SPRITE_BACK_SIZE_ADD = 15.0f;

//=============================================================================
// constructor
//=============================================================================
AssertEffectStart::AssertEffectStart(void)
	:AssertEffect(TYPE_START)
	,sprite_(nullptr)
	,sprite_back_(nullptr)
	,position_(0.0f,0.0f)
	,frame_count_(0)
	,back_move_(true)
	,position_back_(0.0f,0.0f)
{
}

//=============================================================================
// destructor
//=============================================================================
AssertEffectStart::~AssertEffectStart(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool AssertEffectStart::Initialize(void)
{
	sprite_ = new Sprite();
	sprite_->Initialize();
	sprite_->__point(Sprite::POINT_CENTER);
	sprite_->__size(SPRITE_SIZE);
	sprite_->__texture_id(Texture::TEXTURE_ID_GAME_STRING_START);
	sprite_->SetParameter();

	sprite_back_ = new Sprite();
	sprite_back_->Initialize();
	sprite_back_->__point(Sprite::POINT_CENTER);
	sprite_back_->__size(D3DXVECTOR2(SPRITE_BACK_SIZE.x,0.0f));
	sprite_back_->__color(D3DXCOLOR(0.0f,0.0f,0.0f,0.6f));
	sprite_back_->SetParameter();

	D3DXVECTOR2 position = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 1.5f,DEFAULT_SCREEN_HEIGHT * 0.5f);
	D3DXVECTOR2 position_back = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f,DEFAULT_SCREEN_HEIGHT * 0.5f);

	position_ = position;
	position_back_ = position_back;

	sprite_->__position(position_);
	sprite_->SetParameter();
	sprite_back_->__position(position_back);
	sprite_back_->SetParameter();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void AssertEffectStart::Uninitialize(void)
{
	SafeRelease(sprite_);
	SafeRelease(sprite_back_);
}

//=============================================================================
// update
//=============================================================================
void AssertEffectStart::Update(void)
{
	D3DXVECTOR2 vector = D3DXVECTOR2(0.0f,0.0f);

	if(back_move_)
	{
		D3DXVECTOR2 size = sprite_back_->__size();
		size.y += SPRITE_BACK_SIZE_ADD;
		if(size.y >= SPRITE_BACK_SIZE.y)
		{
			size.y = SPRITE_BACK_SIZE.y;
			back_move_ = false;
		}
		sprite_back_->__size(size);
		sprite_back_->SetParameter();
	}
	else
	{
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
			purpose_position_ = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * -0.5f,DEFAULT_SCREEN_HEIGHT * 0.5f);
			vector = purpose_position_ - position_;
			position_ = position_ + vector * 1.0f / (f32)SRIDE_OUT_FRAME * (f32)(frame_count_ - SRIDE_IN_FRAME - STOP_FRAME);

			D3DXVECTOR2 size = sprite_back_->__size();
			size.y -= SPRITE_BACK_SIZE_ADD;
			if(size.y <= 0.0f)
			{
				size.y = 0.0f;
			}
			sprite_back_->__size(size);
			sprite_back_->SetParameter();
		}
		else
		{
			is_assert_ = false;
		}
	}
}

//=============================================================================
// draw
//=============================================================================
void AssertEffectStart::Draw(void)
{
	if(is_assert_)
	{
		sprite_back_->__position(position_back_);
		sprite_back_->Draw();

		sprite_->__position(position_);
		sprite_->Draw();
	}
}

//---------------------------------- EOF --------------------------------------
