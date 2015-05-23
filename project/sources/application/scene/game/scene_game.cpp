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
}

//=============================================================================
// update
//=============================================================================
void SceneGame::Update(void)
{
	// update stage offset
	stage_offset_->Update();

	// set offset position
	stage_->__offset_position(stage_offset_->__position());

	// update stage
	stage_->Update();
}

//=============================================================================
// draw
//=============================================================================
void SceneGame::Draw(void)
{
	// draw stage
	stage_->Draw();
}

//=============================================================================
// create factory
//=============================================================================
SceneFactory* SceneGame::CreateFactory(void)const
{
	return new GameFactory();
}

//---------------------------------- EOF --------------------------------------
