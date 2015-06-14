//*****************************************************************************
//
// stage tutorial
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "stage_tutorial.h"
#include "stage_factory.h"
#include "../game_player.h"
#include "object/map.h"
#include "object/stage_offset.h"
#include "../../factory/scene_factory.h"
#include "system/system.h"
#include "object/object_start_point.h"
#include "collision/collision_map.h"

//*****************************************************************************
// constant definition
//*****************************************************************************

//=============================================================================
// constructor
//=============================================================================
StageTutorial::StageTutorial(void)
	:Stage(TYPE_TUTORIAL)
	,game_player_(nullptr)
	,map_(nullptr)
	,time_count_(0)
{
}

//=============================================================================
// destructor
//=============================================================================
StageTutorial::~StageTutorial(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool StageTutorial::Initialize(void)
{
	game_player_ = new GamePlayer();

	if(!SafeInitialize(game_player_))
	{
		return false;
	}
	game_player_->__position(D3DXVECTOR2(100.0f,0.0f));

	map_ = new Map();

	if(!SafeInitialize(map_))
	{
		return false;
	}

	map_->LoadFromFile("data/map/map.bin");

	stage_offset_ = new StageOffset();

	if(!SafeInitialize(stage_offset_))
	{
		return false;
	}

	stage_offset_->__screen_size(D3DXVECTOR2((f32)DEFAULT_SCREEN_WIDTH,(f32)DEFAULT_SCREEN_HEIGHT));
	stage_offset_->__stage_size(map_->__size());

	object_start_point_ = new ObjectStartPoint();
	object_start_point_->Initialize();
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void StageTutorial::Uninitialize(void)
{
	SafeRelease(game_player_);

	SafeRelease(map_);

	SafeRelease(stage_offset_);
}

//=============================================================================
// update
//=============================================================================
void StageTutorial::Update(void)
{
	time_count_++;

	game_player_->Update();

	stage_offset_->__reference_position(game_player_->__position());
	stage_offset_->Update();

	game_player_->__offset_position(stage_offset_->__position());

	map_->__position(-stage_offset_->__position());
	D3DXVECTOR2 player_position = game_player_->__position();
	D3DXVECTOR2 player_old_position = game_player_->__old_position();
	D3DXVECTOR2 index_position;
	u32 index = 0;
	CollisionMap collision_map;

	index = map_->GetIndex(D3DXVECTOR2(player_position.x - game_player_->__size().x * 0.5f,player_position.y - game_player_->__size().y * 0.5f),&index_position);

	if(index != 0)
	{
		if(collision_map.IsHit(player_position,player_old_position,index_position,game_player_->__size().x,game_player_->__size().y,128,128))
		{
			game_player_->HitStage(collision_map.__position(),true);
		}
	}

	index = map_->GetIndex(D3DXVECTOR2(player_position.x - game_player_->__size().x * 0.5f,player_position.y + game_player_->__size().y * 0.5f),&index_position);

	if(index != 0)
	{
		if(collision_map.IsHit(player_position,player_old_position,index_position,game_player_->__size().x,game_player_->__size().y,128,128))
		{
			game_player_->HitStage(collision_map.__position(),true);
		}
	}

	index = map_->GetIndex(D3DXVECTOR2(player_position.x + game_player_->__size().x * 0.5f,player_position.y - game_player_->__size().y * 0.5f),&index_position);

	if(index != 0)
	{
		if(collision_map.IsHit(player_position,player_old_position,index_position,game_player_->__size().x,game_player_->__size().y,128,128))
		{
			game_player_->HitStage(collision_map.__position(),true);
		}
	}

	index = map_->GetIndex(D3DXVECTOR2(player_position.x + game_player_->__size().x * 0.5f,player_position.y + game_player_->__size().y * 0.5f),&index_position);

	if(index != 0)
	{
		if(collision_map.IsHit(player_position,player_old_position,index_position,game_player_->__size().x,game_player_->__size().y,128,128))
		{
			game_player_->HitStage(D3DXVECTOR2(collision_map.__position().x,collision_map.__position().y),true);
		}
	}

	if(game_player_->__position().y > map_->__size().y)
	{
		game_player_->Dead();
	}

	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_P))
	{
		next_scene_factory_ = new TitleFactory();
	}
}

//=============================================================================
// draw
//=============================================================================
void StageTutorial::Draw(void)
{
	object_start_point_->Draw();
	game_player_->Draw();

	map_->Draw();
}

//=============================================================================
// create factory
//=============================================================================
StageFactory* StageTutorial::CreateFactory(void)const
{
	return new TutorialFactory();
}

//---------------------------------- EOF --------------------------------------
