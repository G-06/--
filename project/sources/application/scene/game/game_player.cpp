//*****************************************************************************
//
// game player
//
// Author		: Ryotaro Arai
//				: Kenji Kabutomori
//				: Taichi Kitazawa
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
const f32 GamePlayer::LIGHT_SPEED = (27.0f);
const f32 GamePlayer::LIGHT_SPEED_MAX = (40.0f);
const f32 GamePlayer::SPEED = (1.75f);
const f32 GamePlayer::DECREMENT = (0.9f);
const f32 GamePlayer::JUMP_SPEED = (-70.0f);
const s32 GamePlayer::DEFAULT_LIFE_MAX = 3;
const s32 GamePlayer::DEFAULT_SP_MAX = 60;
const s32 GamePlayer::DEFAULT_SP_RECOVER_SPEED = 2;
const D3DXVECTOR2 GamePlayer::DEFAULT_SIZE = D3DXVECTOR2(120.0f,197.0f);
const u32 GamePlayer::DEAD_TIME = 45;		//死ぬアニメのフレーム数の合計
const u32 GamePlayer::OUT_WABISABI = 80;	//ワープして消えた後の余韻
const f32 GamePlayer::NEKO_FADE_IN = 0.03f;	
const f32 GamePlayer::WARP_SPD_Y=15.f;
const f32 GamePlayer::WARP_SPD_X=10.f;


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
	,locus_counter_(0)
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
	color_ = D3DXCOLOR(1.0f,1.0f,1.0f,0.0f);
	player_->__color(color_);
	player_->Update();
	lightning_start_ = nullptr;
	nyas_dead_ = nullptr;
	for(s32 i = 0; i < LOCUS_NUM; i++)
	{
		nyas_locus_[i] = new EffectLocus();
		nyas_locus_[i]->Initialize();
	}
	light_speed_ = LIGHT_SPEED;

	Status_ = CAT_STATUS_STAGE_IN;

	dead_cnt_ = 0;
	warp_cnt_ = 0;
	warp_out_ = false;
	is_light_accele_ = false;
	is_preview_light_accele_ = false;

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
	for(s32 i = 0; i < LOCUS_NUM; i++)
	{
		SafeRelease(nyas_locus_[i]);
	}
}

//=============================================================================
// update
//=============================================================================
void GamePlayer::Update(void)
{
	switch(Status_)
	{
	case CAT_STATUS_LIVE:	//生きてるときの更新
		UpdateLive();
		break;
	case CAT_STATUS_DEAD:	//死んでるときの更新
		UpdateDead();
		break;
	case CAT_STATUS_CLEAR:	//クリアしたときの更新
		UpdateClear();
		break;
	case CAT_STATUS_WARP:	//ワープするときの更新
		UpdateWarp();
		break;
	case CAT_STATUS_STAGE_IN:	//ワープするときの更新
		UpdateStageIn();
		break;
	}
}

//=============================================================================
// ステージに入るときの更新
//=============================================================================
void GamePlayer::UpdateStageIn(void)
{
	player_->__color(color_);
	if(color_.a>=1.0f)
	{
		color_.a = 1.0f;
		Status_ = CAT_STATUS_LIVE;
	}

	color_.a+=NEKO_FADE_IN;

	UpdateLive();

}


//=============================================================================
// ネコが生きてるときの更新
//=============================================================================
void GamePlayer::UpdateLive(void)
{
	is_preview_light_accele_ = is_light_accele_;
	is_preview_light_ = is_force_light_;
	is_light_accele_ = false;
	if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_VIRTUAL_RIGHT))		//右行くとき
	{
		Move(1.0);
	}
	else if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_VIRTUAL_LEFT))	//左行くとき
	{
		Move(-1.0);
	}

	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_CANCEL))	//ジャンプ
	{
		Jump();
	}

	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_LIGHT))	//光化
	{
		D3DXVECTOR2 vector = D3DXVECTOR2(0.0f,0.0f);

		if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_VIRTUAL_UP))	//光化方向
		{
			vector.y = -1.0f;
		}
		if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_VIRTUAL_DOWN))	//光化方向
		{
			vector.y = 1.0f;
		}
		if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_VIRTUAL_LEFT))	//光化方向
		{
			vector.x = -1.0f;
		}
		if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_VIRTUAL_RIGHT))	//光化方向
		{
			vector.x = 1.0f;
		}
		ChangeLightMode(vector);
	}

	if(!GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_VIRTUAL_LIGHT))	//光化解除？
	{
		StopLightMode();
	}

	if(is_light_ == false)		//光化してないとき？
	{
		locus_counter_ = 0;
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
		else	//空中にいるとき
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
			sp_ = sp_max_;
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
	else	//光化しているとき？
	{
		locus_counter_++;
		
		for(s32 i = 0; i < LOCUS_NUM; i++)
		{
			if(nyas_locus_[i]->__is_free())
			{
				nyas_locus_[i]->__position(position_);
				nyas_locus_[i]->__offset_position(offset_position_);
				nyas_locus_[i]->Start();
				break;
			}
		}
		
		if(is_sp_recover_speed_up_)
		{
			sp_ = sp_max_;
			is_enable_light_ = true;
		}
		else
		{
			sp_--;
			if(sp_ <= 0 || sp_ > sp_max_)
			{
				sp_ = 0;
				StopLightMode();
			}
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

	if(lightning_start_)	//光化はじめ？
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
	for(s32 i = 0; i < LOCUS_NUM; i++)
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
// ネコが死んでるときの更新
//=============================================================================
void GamePlayer::UpdateDead(void)
{
	if(lightning_start_)	//光化はじめ？
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

	for(s32 i = 0; i < LOCUS_NUM; i++)
	{
		if(!nyas_locus_[i]->__is_free())
		{
			nyas_locus_[i]->__offset_position(offset_position_);
			nyas_locus_[i]->Update();
		}
		
	}

	player_->StartAnimation(ObjectPlayer::ANIMATION_TYPE_DEAD);
	player_->Update();

	if(dead_cnt_ == DEAD_TIME)	//死ぬエフェクトが終わった時
	{
		if(life_ > 0)
		{
			Status_ = CAT_STATUS_LIVE;
			position_ = return_position_;
			old_position_ = position_;
			dead_cnt_ = 0;
		}
	}
	dead_cnt_++;
}

//=============================================================================
// ネコがクリアした時の更新
//=============================================================================
void GamePlayer::UpdateClear(void)
{
	player_->StartAnimation(ObjectPlayer::ANIMATION_TYPE_JOY);

	is_force_light_ = false;
	is_preview_light_ = false;
	if(lightning_start_)	//光化はじめ？
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
	for(s32 i = 0; i < LOCUS_NUM; i++)//光化中
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
	is_fly_ = true;
	is_force_light_ = false;

	move_.y += DEFAULT_GRAVITY;
	move_ *= DECREMENT;

	old_position_ = position_;
	D3DXVECTOR2 t_move = move_;
	D3DXVECTOR2 t_acceleration = acceleration_;
	t_move.x = 0.0f;
	t_acceleration.x = 0.0f;
	position_ += t_move + t_acceleration;
	acceleration_ = D3DXVECTOR2(0.0f,0.0f);
	StopLightMode();

	player_->__is_flip(is_left_);
	player_->Update();
	is_sp_down_ = false;
	is_sp_recover_speed_up_ = false;
	sp_recover_speed_ = DEFAULT_SP_RECOVER_SPEED;
}

//=============================================================================
//ワープしてるときの更新
//=============================================================================
void GamePlayer::UpdateWarp(void)
{
	D3DXVECTOR2 size;
	warp_cnt_++;

	player_->StartAnimation(ObjectPlayer::ANIMATION_TYPE_LIGHT);

	if(warp_cnt_>=20)
	{
		size = player_->__Get_size();
		size.y-=WARP_SPD_Y;
		player_->SetSize(size);
		if((size.y < 0)&&(warp_cnt_>=80))
		{
			warp_out_ = true;
		}
	}

	player_->Update();
}

//=============================================================================
// draw
//=============================================================================
void GamePlayer::Draw(void)
{
	
	for(s32 i = 0; i < LOCUS_NUM; i++)
	{
		if(!nyas_locus_[i]->__is_free())
		{
			nyas_locus_[i]->Draw();
		}
		
	}

	if(lightning_start_)	//光化エフェクト？
	{
		lightning_start_->Draw();
	}

#ifndef _RELEASE
	DEBUG_TOOL.__debug_display()->Print("player position(%.1f,%.1f)\n",position_.x,position_.y);
#endif // _RELEASE

	player_->__position(position_ - offset_position_);
	player_->Draw();	//プレイヤー
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
		GET_SE->Play(SE::SE_ID_NYAS_JUMP);
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

	if(is_light_)
	{
		GET_SE->Play(SE::SE_ID_NYAS_LIGHT_COLLISION);
	}

	StopLightMode();
	//is_light_ = false;

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
		if(!is_force_light_)
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
						move_.x = -light_speed_;
						move_.y = 0.0f;
					}
					else
					{
						move_.x = light_speed_;
						move_.y = 0.0f;
					}
				}
				else
				{
					move_ = normalize_vector * light_speed_;
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
				GET_SE->Play(SE::SE_ID_NYAS_LIGHT_START);
			}
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
		if(is_light_)
		{
			GET_SE->Play(SE::SE_ID_NYAS_LIGHT_END);
			is_light_ = false;
			light_speed_ = LIGHT_SPEED;
		}
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
		move_ = normalize_vector * light_speed_;
	}
}

//=============================================================================
//死んだとき
//=============================================================================
void GamePlayer::Dead(void)
{
	if(Status_ != CAT_STATUS_DEAD)
	{
		life_--;

		is_enable_light_ = true;
		is_light_ = false;
		move_ = D3DXVECTOR2(0.0f,0.0f);
		Status_ = CAT_STATUS_DEAD;
		GET_SE->Play(SE::SE_ID_DEATH);
		light_speed_ = LIGHT_SPEED;
	}
}

//=============================================================================
// Heal
//=============================================================================
void GamePlayer::Heal(u32 health)
{

	life_ += health;
	if(life_ > DEFAULT_LIFE_MAX)
	{
		life_ = DEFAULT_LIFE_MAX;
	}

}

//=============================================================================
// clear
//=============================================================================
void GamePlayer::Clear(void)
{
	Status_ = CAT_STATUS_CLEAR;
	is_force_light_ = false;
	StopLightMode();
}

//=============================================================================
// light accele
//=============================================================================
bool GamePlayer::LightAccele(const f32& speed)
{
	if(!is_preview_light_accele_)
	{
		if(!is_light_accele_)
		{
			if(is_light_)
			{
				is_light_accele_ = true;
				light_speed_ *= speed;

				if(light_speed_ > LIGHT_SPEED_MAX)
				{
					light_speed_ = LIGHT_SPEED_MAX;
				}
				D3DXVECTOR2 vector;
				D3DXVec2Normalize(&vector,&move_);

				move_ = vector * light_speed_;
				return true;
			}
		}
	}
	return false;
}

//---------------------------------- EOF --------------------------------------
