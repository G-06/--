//*****************************************************************************
//
// game player
//
// Author		: Ryotaro Arai
//				: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "game_player.h"
#include "application/object/object_player.h"
#include "system/system.h"
#include "system/direct_input/input_event_buffer.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const f32 GamePlayer::LIGHT_SPEED = (30.0f);
const f32 GamePlayer::SPEED = (2.0f);
const f32 GamePlayer::DECREMENT = (0.9f);
const f32 GamePlayer::JUMP_SPEED = (-70.0f);

//=============================================================================
// constructor
//=============================================================================
GamePlayer::GamePlayer(void)
	:player_(nullptr)
{
}

//=============================================================================
// destructor
//=============================================================================
GamePlayer::~GamePlayer(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool GamePlayer::Initialize(void)
{
	position_				= D3DXVECTOR2(0, 0);
	old_position_			= position_;
	move_					= D3DXVECTOR2(0, 0);
	size_					= D3DXVECTOR2(200, 200);
	offset_position_		= D3DXVECTOR2(0, 0);
	acceleration_counter_	= 0;
	slowdown_counter_		= 0;
	is_left_				= false;
	is_light_				= false;
	is_fly_					= true;
	is_enable_light_		= true;
	player_= new ObjectPlayer();
	player_->Initialize();
	player_->__position(position_);

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void GamePlayer::Uninitialize(void)
{
	SafeRelease(player_);
}

//=============================================================================
// update
//=============================================================================
void GamePlayer::Update(void)
{
	if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_VIRTUAL_RIGHT))
	{
		Move(1.0);
	}
	else if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_VIRTUAL_LEFT))
	{
		Move(-1.0);
	}

	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_CANCEL))
	{
		Jump();
	}

	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_6))
	{
		D3DXVECTOR2 vector = D3DXVECTOR2(0.0f,0.0f);

		if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_VIRTUAL_UP))
		{
			vector.y = -1.0f;
		}
		if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_VIRTUAL_DOWN))
		{
			vector.y = 1.0f;
		}
		if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_VIRTUAL_LEFT))
		{
			vector.x = -1.0f;
		}
		if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_VIRTUAL_RIGHT))
		{
			vector.x = 1.0f;
		}

		ChangeLightMode(vector);
	}

	if(GET_DIRECT_INPUT->CheckRelease(INPUT_EVENT_VIRTUAL_6))
	{
		StopLightMode();
	}

	if(is_light_ == false)
	{
		if(is_fly_ == false)
		{
			if(move_.x <= 0.9f && move_.x >= -0.9f)
			{
				move_.x = 0.0f;
				player_->StartAnimation(ObjectPlayer::ANIMATION_TYPE_WAIT);
			}
			else
			{
				player_->StartAnimation(ObjectPlayer::ANIMATION_TYPE_RUN);
			}
		}
		else
		{
			player_->StartAnimation(ObjectPlayer::ANIMATION_TYPE_FALL);
		}

		move_.y += DEFAULT_GRAVITY;
		move_ *= DECREMENT;

	}

	is_fly_ = true;
	old_position_ = position_;
	position_ += move_;

	player_->__is_flip(is_left_);
	player_->Update();
}

//=============================================================================
// draw
//=============================================================================
void GamePlayer::Draw(void)
{
	player_->__position(position_ - offset_position_);
	player_->Draw();
}

//=============================================================================
// move
//=============================================================================
void GamePlayer::Move(f32 vector)
{
	if(!is_light_)
	{
		if(vector > 0.0f)
		{
			is_left_ = false;
			move_.x += SPEED;
		}
		else
		{
			is_left_ = true;
			move_.x -= SPEED;
		}
	}
}

//=============================================================================
// jump
//=============================================================================
void GamePlayer::Jump(void)
{
	if(!is_fly_)
	{
		is_fly_ = true;
		move_.y = JUMP_SPEED;
		player_->StartAnimation(ObjectPlayer::ANIMATION_TYPE_JUMP);
	}
}

//=============================================================================
// hit stage
//=============================================================================
void GamePlayer::HitStage(const D3DXVECTOR2& position,bool is_floor)
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
// change light mode
//=============================================================================
void GamePlayer::ChangeLightMode(const D3DXVECTOR2& vector)
{
	if(is_enable_light_)
	{
		D3DXVECTOR2 normalize_vector;
		is_enable_light_ = false;
		is_light_ = true;
		is_fly_ = true;
		D3DXVec2Normalize(&normalize_vector,&vector);

		if(normalize_vector.x == 0.0f && normalize_vector.y == 0.0f)
		{
			if(is_left_)
			{
				move_.x = -LIGHT_SPEED;
				move_.y = 0.0f;
			}
			else
			{
				move_.x = LIGHT_SPEED;
				move_.y = 0.0f;
			}
		}
		else
		{
			move_ = normalize_vector * LIGHT_SPEED;
		}

		player_->StartAnimation(ObjectPlayer::ANIMATION_TYPE_LIGHT);
	}
}

//=============================================================================
// stop light mode
//=============================================================================
void GamePlayer::StopLightMode(void)
{
	is_light_ = false;
}

//=============================================================================
// change direction
//=============================================================================
void GamePlayer::ChangeDirection(const D3DXVECTOR2& vector)
{
	if(is_light_)
	{
		D3DXVECTOR2 normalize_vector;
		D3DXVec2Normalize(&normalize_vector,&vector);
		move_ = normalize_vector * LIGHT_SPEED;
	}
}

//---------------------------------- EOF --------------------------------------
