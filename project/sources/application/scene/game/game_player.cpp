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
#include "effect/effect_lightning.h"
#include "effect/effect_dead.h"
#include "effect/effect_locus.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const f32 GamePlayer::LIGHT_SPEED = (30.0f);
const f32 GamePlayer::SPEED = (1.75f);
const f32 GamePlayer::DECREMENT = (0.9f);
const f32 GamePlayer::JUMP_SPEED = (-70.0f);
const s32 GamePlayer::DEFAULT_LIFE_MAX = 3;
const s32 GamePlayer::DEFAULT_SP_MAX = 60;
const s32 GamePlayer::DEFAULT_SP_RECOVER_SPEED = 2;
const D3DXVECTOR2 GamePlayer::DEFAULT_SIZE = D3DXVECTOR2(190.0f,197.0f);

//=============================================================================
// constructor
//=============================================================================
GamePlayer::GamePlayer(void)
	:player_(nullptr)
	,check_point_priority_(0)
	,acceleration_(0.0f,0.0f)
	,is_preview_light_(false)
	,is_force_light_(false)
	,sp_recover_speed_(2)
	,is_sp_recover_speed_up_(false)
	,is_sp_down_(false)
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
	position_ = D3DXVECTOR2(0,0);
	old_position_ = position_;
	return_position_ = position_;
	move_ = D3DXVECTOR2(0,0);
	size_ = DEFAULT_SIZE;
	offset_position_ = D3DXVECTOR2(0,0);
	is_left_ = false;
	is_light_ = false;
	is_fly_ = true;
	is_enable_light_ = true;
	life_ = DEFAULT_LIFE_MAX;
	sp_max_ = DEFAULT_SP_MAX;
	sp_ = sp_max_;
	player_= new ObjectPlayer();
	player_->Initialize();
	player_->__position(position_);
	lightning_start_ = nullptr;
	nyas_dead_ = nullptr;
	for(s32 i = 0; i < 100; i++)
	{
		nyas_locus_[i] = new EffectLocus();
		nyas_locus_[i]->Initialize();
	}

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void GamePlayer::Uninitialize(void)
{
	SafeRelease(player_);
	SafeRelease(lightning_start_);
	SafeRelease(nyas_dead_);
	for(s32 i = 0; i < 100; i++)
	{
		SafeRelease(nyas_locus_[i]);
	}
}

//=============================================================================
// update
//=============================================================================
void GamePlayer::Update(void)
{
	is_preview_light_ = is_force_light_;

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

	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_LIGHT))
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

	if(!GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_VIRTUAL_LIGHT))
	{
		StopLightMode();
	}
	
	if(is_light_ == false)
	{
		if(is_fly_ == false)
		{
			if(move_.x <= 0.9f && move_.x >= -0.9f)
			{
				if(!(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_VIRTUAL_LEFT) || GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_VIRTUAL_RIGHT)))
				{
					move_.x = 0.0f;
					player_->StartAnimation(ObjectPlayer::ANIMATION_TYPE_WAIT);
				}
			}
			else
			{
				player_->StartAnimation(ObjectPlayer::ANIMATION_TYPE_RUN);
			}
		}
		else
		{
			if(player_->__animation_type() != ObjectPlayer::ANIMATION_TYPE_JUMP)
			{
				player_->StartAnimation(ObjectPlayer::ANIMATION_TYPE_FALL);
			}
		}

		move_.y += DEFAULT_GRAVITY;
		move_ *= DECREMENT;

		if(is_sp_recover_speed_up_)
		{
			sp_recover_speed_ = sp_max_;
			is_enable_light_ = true;
		}

		if(is_sp_down_)
		{

		}
		else
		{
			sp_ += sp_recover_speed_;
		}

		if(sp_ > sp_max_)
		{
			sp_ = sp_max_;
		}
	}
	else
	{
		for(s32 i = 0; i < 100; i++)
		{
			if(nyas_locus_[i]->__is_free())
			{
				nyas_locus_[i]->__position(position_);
				nyas_locus_[i]->__offset_position(offset_position_);
				nyas_locus_[i]->Start();
				break;
			}
		}

		sp_--;
		if(sp_ <= 0 || sp_ > sp_max_)
		{
			sp_ = 0;
			StopLightMode();
		}
	}

	if(is_sp_down_)
	{
		sp_--;
	}

	if(sp_ <= 0)
	{
		sp_ = 0;
	}

	is_fly_ = true;
	is_force_light_ = false;
	old_position_ = position_;
	position_ += move_ + acceleration_;
	acceleration_ = D3DXVECTOR2(0.0f,0.0f);

	player_->__is_flip(is_left_);
	player_->Update();
	is_sp_down_ = false;
	is_sp_recover_speed_up_ = false;
	sp_recover_speed_ = DEFAULT_SP_RECOVER_SPEED;

	if(lightning_start_)
	{
		lightning_start_->__offset_position(offset_position_);
		lightning_start_->Update();

		if(lightning_start_->__is_death())
		{
			lightning_start_->Uninitialize();
			delete lightning_start_;
			lightning_start_ = nullptr;
		}
	}
	if(nyas_dead_)
	{
		nyas_dead_->__offset_position(offset_position_);
		nyas_dead_->Update();

		if(nyas_dead_->__is_death())
		{
			nyas_dead_->Uninitialize();
			delete nyas_dead_;
			nyas_dead_ = nullptr;
		}
	}
	for(s32 i = 0; i < 100; i++)
	{
		if(!nyas_locus_[i]->__is_free())
		{
			nyas_locus_[i]->__offset_position(offset_position_);
			nyas_locus_[i]->Update();

			if(nyas_locus_[i]->__is_death())
			{
				nyas_locus_[i]->__is_free(true);
			}
		}
	}
}

//=============================================================================
// draw
//=============================================================================
void GamePlayer::Draw(void)
{
	for(s32 i = 0; i < 100; i++)
	{
		if(!nyas_locus_[i]->__is_free())
		{
			nyas_locus_[i]->Draw();
		}
	}

	if(lightning_start_)
	{
		lightning_start_->Draw();
	}
	if(nyas_dead_)
	{
		nyas_dead_->Draw();
	}
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
// accelerate
//=============================================================================
void GamePlayer::Accelerate(const D3DXVECTOR2& acceleration)
{
	acceleration_ += acceleration;
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
		if(sp_ > 0)
		{
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
			if(lightning_start_)
			{
				lightning_start_->Uninitialize();
				delete lightning_start_;
				lightning_start_ = nullptr;
			}
			lightning_start_ = new EffectLightning();
			lightning_start_->Initialize();
			lightning_start_->__position(position_);
			lightning_start_->__offset_position(offset_position_);
		}
	}
}

//=============================================================================
// stop light mode
//=============================================================================
void GamePlayer::StopLightMode(void)
{
	if(!is_force_light_)
	{
		is_light_ = false;
	}
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

//=============================================================================
// dead
//=============================================================================
void GamePlayer::Dead(void)
{
	if(life_ > 0)
	{
		life_--;
		nyas_dead_ = new EffectDead();
		nyas_dead_->Initialize();
		nyas_dead_->__position(position_);
		nyas_dead_->__offset_position(offset_position_);

		position_ = return_position_;
		old_position_ = position_;
		is_enable_light_ = true;
		is_light_ = false;
		move_ = D3DXVECTOR2(0.0f,0.0f);
	}
	else
	{
		life_--;
	}
}

//=============================================================================
// clear
//=============================================================================
void GamePlayer::Clear(void)
{
}

//---------------------------------- EOF --------------------------------------
