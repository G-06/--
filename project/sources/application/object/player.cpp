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

const f32 Player::LIGHT_SPEED = (30.0f);
const f32 Player::MAX_SPEED = (20.0f);
const f32 Player::JUMP_SPEED = (-20.0f);

const Animation::DATA Player::ANIMATION_DATA[] =
{
	Animation::DATA(2, 1, ANIMATION_RUN_START),
	Animation::DATA(2, 2, 1),
	Animation::DATA(2, 3, 2),
	Animation::DATA(2, 4, 3),
	Animation::DATA(2, 5, 4),
	Animation::DATA(2, 6, 5),
	Animation::DATA(2, 7, 6),
	Animation::DATA(2, 8, 7),
	Animation::DATA(2, 9, 8),
	Animation::DATA(2, ANIMATION_RUN_START, 9)
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
	size_					= D3DXVECTOR2(100, 200);
	offset_position_		= D3DXVECTOR2(0, 0);
	acceleration_counter_	= 0;
	slowdown_counter_		= 0;
	is_right_				= true;
	is_light_				= false;
	is_fly_					= false;
	
	player_= new Sprite();
	animation_ = new Animation();
	animation_->Add(ANIMATION_DATA, sizeof(ANIMATION_DATA));
	player_->Initialize();
	player_->__size(size_);
	player_->__position(position_);
	player_->__texture_id(Texture::TEXTURE_ID_ANIM_TEST);
	player_->__division_height(2);
	player_->__division_width(5);
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
	old_position_ = position_;

	if(is_light_ == false)
	{
		move_.y += DEFAULT_GRAVITY;

		if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_RIGHT) || GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_PAD_3))
		{
			is_right_ = true;

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
			is_right_ = false;

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

		if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_Z) && is_fly_ == false || GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_PAD_4) && is_fly_ == false)
		{
			is_fly_ = true;
			move_.y = JUMP_SPEED;
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
				animation_->Stop();
			}
		}

		if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_X) && is_fly_ == false || GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_PAD_9) && is_fly_ == false)
		{
			LightMode(true, is_right_);
		}
	}else
	{
		if(GET_DIRECT_INPUT->CheckRelease(INPUT_EVENT_X) || GET_DIRECT_INPUT->CheckRelease(INPUT_EVENT_PAD_9))
		{
			LightMode(false, is_right_);
		}
	}

	position_ += move_;

	animation_->Update();

	player_->__is_flip(is_right_);
	if(move_.x != 0)
	{
		player_->__index(animation_->__current_index());
	}
	else
	{
		player_->__index(ANIMATION_RUN_START);
	}
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
// stagecollision
//=============================================================================
void Player::Stagecollision(u32 mode, D3DXVECTOR2 stage_size)
{
	switch(mode)
	{
		case COLLISION_DOWN:
			position_.y = stage_size.y - size_.y;
			is_fly_ = false;
			break;

		case COLLISION_RIGHT:
			position_.x = stage_size.x - size_.x;
			if(is_light_)
			{
				LightMode(false, is_right_);
			}
			animation_->Stop();
			player_->__index(ANIMATION_RUN_START);
			player_->SetParameter();
			break;

		case COLLISION_LEFT:
			if(is_light_)
			{
				LightMode(false, is_right_);
			}
			position_.x = 0.0f;
			animation_->Stop();
			player_->__index(ANIMATION_RUN_START);
			player_->SetParameter();
			break;

		default:
			break;
	}
}

//=============================================================================
// lightmode
//=============================================================================
void Player::LightMode(bool is_light, bool is_right)
{
	if(is_light == true)
	{
		if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_UP) || GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_PAD_0))
		{
			move_.y = -LIGHT_SPEED;
		}

		if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_RIGHT) || GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_PAD_3))
		{
			move_.x = LIGHT_SPEED;
		}
		else if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_LEFT) || GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_PAD_2))
		{
			move_.x = -LIGHT_SPEED;
		}

		if(!GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_RIGHT) && 
			!GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_LEFT) && 
			!GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_PAD_3) &&
			!GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_PAD_2) &&
			!GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_UP) && 
			!GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_PAD_0))
		{
			if(is_right == true)
			{
				move_.x = LIGHT_SPEED;
			}
			else
			{
				move_.x = -LIGHT_SPEED;
			}
		}

		is_fly_ = true;
		is_light_ = true;
		// Žd—l•s–¾ ‚Æ‚è‚ ‚¦‚¸ÃŽ~
		animation_->Stop();
		animation_->__current_index(ANIMATION_RUN_START);
	}
	else
	{
		move_.x = 0;
		move_.y = 0;

		is_light_ = false;
	}
}


//---------------------------------- EOF --------------------------------------
