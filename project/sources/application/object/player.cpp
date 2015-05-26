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
	is_left_				= false;
	is_light_				= false;
	is_fly_					= false;
	
	player_= new Sprite();
	player_->Initialize();
	player_->__size(size_);
	player_->__position(position_);
	player_->__texture_id(Texture::TEXTURE_ID_ANIM_TEST);
	player_->SetParameter();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void Player::Uninitialize(void)
{
	SafeRelease(player_);
}

//=============================================================================
// update
//=============================================================================
void Player::Update(void)
{
	old_position_ = position_;

	if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_RIGHT))
	{
		is_left_ = false;

		if(move_.x <= 0)
		{
			move_.x = 1;
			acceleration_counter_ = 0;
		}

		acceleration_counter_++;

		if(acceleration_counter_ % 1 == 0 && move_.x < 20)
		{
			move_.x+=0.5f;
		}
	}

	if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_LEFT))
	{
		is_left_ = true;

		if(move_.x >= 0)
		{
			move_.x = -1;
			acceleration_counter_ = 0;
		}

		acceleration_counter_++;

		if(acceleration_counter_ % 1 == 0 && move_.x > -20)
		{
			move_.x-=0.5f;
		}
	}

	if(!GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_RIGHT) && !GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_LEFT) && move_.x != 0)
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

	position_ += move_;

	player_->__position(position_);
	player_->SetParameter();
}

//=============================================================================
// draw
//=============================================================================
void Player::Draw(void)
{
	player_->Draw();
}


//---------------------------------- EOF --------------------------------------
