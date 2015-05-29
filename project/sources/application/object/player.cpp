//*****************************************************************************
//
// player
//
// Author		: Ryotaro Arai
//				: Kenji Kabutomori
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
const f32 Player::SPEED = (2.0f);
const f32 Player::DECREMENT = (0.9f);
const f32 Player::JUMP_SPEED = (-70.0f);
const u32 Player::ANIMATION_RUN_START = (0);
const u32 Player::ANIMATION_WAIT_START = (6);
const u32 Player::ANIMATION_LIGHT_START = (7);
const Animation::DATA Player::ANIMATION_DATA[] =
{
	Animation::DATA(4, 1, 0),
	Animation::DATA(4, 2, 1),
	Animation::DATA(4, 3, 2),
	Animation::DATA(4, 4, 3),
	Animation::DATA(4, 5, 4),
	Animation::DATA(4, 0, 5),
	Animation::DATA(2, 6, 0),
	Animation::DATA(2, 7, 0),
};
const Player::ANIMATION_TEXTURE_DATA Player::TEXTURE_DATA[ANIMATION_TYPE_MAX] =
{
	ANIMATION_TEXTURE_DATA(Texture::TEXTURE_ID_PLAYER,3,2),
	ANIMATION_TEXTURE_DATA(Texture::TEXTURE_ID_PLAYER,3,2),
	ANIMATION_TEXTURE_DATA(Texture::TEXTURE_ID_LIGHT,1,1),
};

//=============================================================================
// constructor
//=============================================================================
Player::Player(void)
	:player_(nullptr)
	,animation_(nullptr)
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
	is_fly_					= true;
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
		if(move_.x <= 0.9f && move_.x >= -0.9f)
		{
			move_.x = 0.0f;
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

		move_.y += DEFAULT_GRAVITY;
		move_ *= DECREMENT;

	}

	is_fly_ = true;
	old_position_ = position_;
	position_ += move_;

	animation_->Update();
	player_->__texture_id((Texture::TEXTURE_ID)TEXTURE_DATA[animation_type_]._texture_id);
	player_->__division_width((Texture::TEXTURE_ID)TEXTURE_DATA[animation_type_]._division_width);
	player_->__division_height((Texture::TEXTURE_ID)TEXTURE_DATA[animation_type_]._division_height);
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
// move
//=============================================================================
void Player::Move(f32 vector)
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
void Player::Jump(void)
{
	if(!is_fly_)
	{
		is_fly_ = true;
		move_.y = JUMP_SPEED;
	}
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
// change light mode
//=============================================================================
void Player::ChangeLightMode(const D3DXVECTOR2& vector)
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

		if(animation_type_ != ANIMATION_TYPE_LIGHT)
		{
			animation_type_ = ANIMATION_TYPE_LIGHT;
			animation_->Start(ANIMATION_LIGHT_START);
		}
	}
}

//=============================================================================
// stop light mode
//=============================================================================
void Player::StopLightMode(void)
{
	is_light_ = false;
}

//=============================================================================
// change direction
//=============================================================================
void Player::ChangeDirection(const D3DXVECTOR2& vector)
{
	if(is_light_)
	{
		D3DXVECTOR2 normalize_vector;
		D3DXVec2Normalize(&normalize_vector,&vector);
		move_ = normalize_vector * LIGHT_SPEED;
	}
}

//---------------------------------- EOF --------------------------------------
