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
	game_player_->Update();

	stage_offset_->__reference_position(game_player_->__position());
	stage_offset_->Update();

	game_player_->__offset_position(stage_offset_->__position());

	map_->__position(-stage_offset_->__position());
	D3DXVECTOR2 player_position = game_player_->__position();
	D3DXVECTOR2 index_position;
	u32 index = map_->GetIndex(player_position,&index_position);

	if(index != 0)
	{
		if(player_position.y >= index_position.y - 64)
		{
			player_position.y = index_position.y - 64;
			game_player_->HitStage(player_position,true);
		}
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
