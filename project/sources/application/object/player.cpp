//*****************************************************************************
//
// player
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "player.h"

#include "render/sprite.h"
#include "system/system.h"
#include "system/direct_input/input_event_buffer.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const f32 Player::LIGHT_SPEED = (30.0f);
const f32 Player::MAX_SPEED = (20.0f);
const f32 Player::JUMP_SPEED = (-20.0f);
const Animation::DATA Player::ANIMATION_DATA[] =
{
	Animation::DATA(2, 1, 0),
	Animation::DATA(2, 2, 1),
	Animation::DATA(2, 3, 2),
	Animation::DATA(2, 4, 3),
	Animation::DATA(2, 5, 4),
	Animation::DATA(2, 0, 5),
	Animation::DATA(2, 6, 0),
	Animation::DATA(2, 7, 1),
};

//=============================================================================
// constructor
//=============================================================================
Player::Player(void)
{
}

//=============================================================================
// destructor
//=============================================================================
Player::~Player(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool Player::Initialize(void)
{
	position_				= D3DXVECTOR2(0, 0);
	old_position_			= position_;
	move_					= D3DXVECTOR2(0, 0);
	size_					= D3DXVECTOR2(256, 256);
	offset_position_		= D3DXVECTOR2(0, 0);
	acceleration_counter_	= 0;
	slowdown_counter_		= 0;
	is_left_				= false;
	is_light_				= false;
	is_fly_					= false;
	is_enable_light_		= true;
	player_= new Sprite();
	animation_ = new Animation();
	animation_->Add(ANIMATION_DATA, sizeof(ANIMATION_DATA));
	animation_type_ = ANIMATION_TYPE_WAIT;
	player_->Initialize();
	player_->__size(size_);
	player_->__position(position_);
	player_->__texture_id(Texture::TEXTURE_ID_PLAYER);
	player_->__division_height(2);
	player_->__division_width(3);
	player_->__index(ANIMATION_RUN_START);
	player_->SetParameter();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void Player::Uninitialize(void)
{
	SafeRelease(player_);
	SafeRelease(animation_);
}

//=============================================================================
// update
//=============================================================================
void Player::Update(void)
{
	if(is_light_ == false)
	{
		move_.y += DEFAULT_GRAVITY;

		if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_RIGHT) || GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_PAD_3))
		{
			is_left_ = false;

			if(move_.x <= 0)
			{
				move_.x = 1;
				acceleration_counter_ = 0;
				animation_->Start(ANIMATION_RUN_START);
			}

			acceleration_counter_++;

			if(acceleration_counter_ % 1 == 0 && move_.x < MAX_SPEED)
			{
				move_.x+=0.5f;
			}
		}

		else if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_LEFT) || GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_PAD_2))
		{
			is_left_ = true;

			if(move_.x >= 0)
			{
				move_.x = -1;
				acceleration_counter_ = 0;
				animation_->Start(ANIMATION_RUN_START);
			}

			acceleration_counter_++;

			if(acceleration_counter_ % 1 == 0 && move_.x > -MAX_SPEED)
			{
				move_.x-=0.5f;
			}
		}

		if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_CANCEL))
		{
			if(!is_fly_)
			{
				is_fly_ = true;
				move_.y = JUMP_SPEED;
			}
		}

		if(!GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_RIGHT) && 
			!GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_LEFT) && 
			!GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_PAD_3) &&
			!GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_PAD_2) &&
			move_.x != 0)
		{
			slowdown_counter_++;

			if(move_.x > 0 && slowdown_counter_ % 1 == 0)
			{
				move_.x-=0.5f;
			}

			if(move_.x < 0 && slowdown_counter_ % 1 == 0)
			{
				move_.x+=0.5f;
			}

			if(move_.x == 0)
			{
				slowdown_counter_ = 0;
			}
		}

		if(move_.x == 0)
		{
			if(animation_type_ != ANIMATION_TYPE_WAIT)
			{
				animation_type_ = ANIMATION_TYPE_WAIT;
				animation_->Start(ANIMATION_WAIT_START);
			}
		}
		else
		{
			if(animation_type_ != ANIMATION_TYPE_RUN)
			{
				animation_type_ = ANIMATION_TYPE_RUN;
				animation_->Start(ANIMATION_RUN_START);
			}
		}

		if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_6))
		{
			LightMode(true,is_left_);
		}

	}else
	{
		if(GET_DIRECT_INPUT->CheckRelease(INPUT_EVENT_VIRTUAL_6))
		{
			LightMode(false,is_left_);
		}
	}

	old_position_ = position_;
	position_ += move_;

	animation_->Update();
	player_->__index(animation_->__current_index());
	player_->__is_flip(is_left_);
	player_->SetParameter();
}

//=============================================================================
// draw
//=============================================================================
void Player::Draw(void)
{
	player_->__position(position_ - offset_position_);
	player_->Draw();
}

//=============================================================================
// hit stage
//=============================================================================
void Player::HitStage(const D3DXVECTOR2& position,bool is_floor)
{
	position_.x = position.x;

	position_.y = position.y;

	is_light_ = false;
	if(is_floor)
	{
		is_fly_ = false;
		is_enable_light_ = true;
	}
}

//=============================================================================
// lightmode
//=============================================================================
void Player::LightMode(bool is_light, bool is_right)
{
	if(is_light == true)
	{
		if(is_enable_light_)
		{
			move_.y = 0.0f;
			if(is_right == false)
			{
				move_.x = LIGHT_SPEED;
			}
			else
			{
				move_.x = -LIGHT_SPEED;
			}

			if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_VIRTUAL_UP))
			{
				move_.y = -LIGHT_SPEED;
				move_.x = 0.0f;
			}

			if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_VIRTUAL_RIGHT))
			{
				move_.x = LIGHT_SPEED;
			}
			else if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_VIRTUAL_LEFT))
			{
				move_.x = -LIGHT_SPEED;
			}

			is_fly_ = true;
			is_light_ = true;
			is_enable_light_ = false;
			if(animation_type_ != ANIMATION_TYPE_LIGHT)
			{
				animation_type_ = ANIMATION_TYPE_LIGHT;
				animation_->Start(ANIMATION_LIGHT_START);
			}
		}
	}
	else
	{
		is_light_ = false;
	}
}

//---------------------------------- EOF --------------------------------------
