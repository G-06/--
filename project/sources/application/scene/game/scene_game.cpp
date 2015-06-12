//*****************************************************************************
//
// scene game
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "scene_game.h"
#include "scene/factory/scene_factory.h"
#include "system/system.h"
#include "application/object/stage.h"
#include "application/object/stage_offset.h"
#include "object/player.h"
#include "collision/collision_map.h"
//=============================================================================
// constructor
//=============================================================================
SceneGame::SceneGame(void)
	:Scene(TYPE_GAME)
{
}

//=============================================================================
// destructor
//=============================================================================
SceneGame::~SceneGame(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool SceneGame::Initialize(void)
{
	stage_ = new Stage();

	if(!SafeInitialize(stage_))
	{
		return false;
	}

	stage_offset_ = new StageOffset();

	if(!SafeInitialize(stage_offset_))
	{
		return false;
	}

	player_ = new Player();

	if(!SafeInitialize(player_))
	{
		return false;
	}

	collision_ = new CollisionMap();

	if(!SafeInitialize(collision_))
	{
		return false;
	}

	stage_offset_->__screen_size(D3DXVECTOR2((f32)GET_WINDOW->__width(),(f32)GET_WINDOW->__height()));
	stage_offset_->__stage_size(stage_->__size());

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void SceneGame::Uninitialize(void)
{
	SafeDelete(next_scene_factory_);

	// release stage offset
	SafeRelease(stage_offset_);

	// release stage
	SafeRelease(stage_);

	SafeRelease(player_);
}

//=============================================================================
// update
//=============================================================================
void SceneGame::Update(void)
{
	player_->Update();

	stage_offset_->__reference_position(player_->__position());

	// update stage offset
	stage_offset_->Update();

	player_->__offset_position(stage_offset_->__position());

	// set offset position
	stage_->__offset_position(stage_offset_->__position());

	// update stage
	stage_->Update();

	// collision

	if(collision_->IsHit(player_->__position(),player_->__old_position(),D3DXVECTOR2(400,0),(player_->__size().x/2),(player_->__size().y/2),200,200))
	{
		
	}
	if(player_->__position().y + player_->__size().y > stage_->__size().y)
	{
		player_->HitStage(D3DXVECTOR2(player_->__position().x,stage_->__size().y - player_->__size().y),true);
	}

	if(player_->__position().x + player_->__size().x > stage_->__size().x)
	{
		player_->HitStage(D3DXVECTOR2(stage_->__size().x - player_->__size().x,player_->__position().y),false);
	}

	if(player_->__position().x < 0)
	{
		player_->HitStage(D3DXVECTOR2(0.0f,player_->__position().y),false);
	}

	if(player_->__position().y < 0.0f)
	{
		D3DXVECTOR2 vector = player_->__move();
		vector.y *= -1;
		player_->ChangeDirection(vector);
	}
}

//=============================================================================
// draw
//=============================================================================
void SceneGame::Draw(void)
{
	// draw stage
	stage_->Draw();

	player_->Draw();
}

//=============================================================================
// create factory
//=============================================================================
SceneFactory* SceneGame::CreateFactory(void)const
{
	return new GameFactory();
}

//---------------------------------- EOF --------------------------------------
