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
#include "stage/stage_manager.h"

//=============================================================================
// constructor
//=============================================================================
SceneGame::SceneGame(void)
	:Scene(TYPE_GAME)
	,stage_manager_(nullptr)
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
	stage_manager_ = new StageManager();

	if(!SafeInitialize(stage_manager_))
	{
		return false;
	}

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void SceneGame::Uninitialize(void)
{
	SafeRelease(stage_manager_);

	////今のステージ解放
	//switch(current_stage_)
	//{
	//case STAGE_ID_SELECT:
	//	SafeRelease(stage_select_);
	//
	//	break;
	//case STAGE_ID_0:
	//case STAGE_ID_1:
	//case STAGE_ID_2:
	//	// release stage offset
	//	SafeRelease(stage_offset_);
	//	// release stage
	//	SafeRelease(stage_);
	//	SafeRelease(player_);
	//	SafeRelease(map_);
	//	break;
	//}
	//
	//// release fade
	//SafeRelease(fade_);

	SafeDelete(next_scene_factory_);
}

//=============================================================================
// update
//=============================================================================
void SceneGame::Update(void)
{
	stage_manager_->Update();

	////ステージの切り替え 
	//if(next_stage_ != STAGE_ID_MAX)
	//{
	//	if(fade_ ->__type() == Fade::TYPE_NONE)
	//	{
	//		// fade out
	//		fade_->Start(Fade::TYPE_OUT);
	//	}
	//	ChangeNextStage();
	//}
	//
	//if(fade_ ->__type() == Fade::TYPE_FADE)
	//{
	//	fade_->Start(Fade::TYPE_IN);
	//}
	//
	//
	//// update fade
	//fade_->Update();
	//
	////今のステージ更新
	//switch(current_stage_)
	//{
	//case STAGE_ID_SELECT:
	//	stage_select_->Update();
	//
	//	break;
	//case STAGE_ID_0:
	//case STAGE_ID_1:
	//case STAGE_ID_2:
	//	player_->Update();
	//
	//	stage_offset_->__reference_position(player_->__position());
	//
	//	// update stage offset
	//	stage_offset_->Update();
	//
	//	player_->__offset_position(stage_offset_->__position());
	//
	//	// set offset position
	//	stage_->__offset_position(stage_offset_->__position());
	//
	//	// update stage
	//	stage_->Update();
	//
	//	// collision
	//	if(player_->__position().y + player_->__size().y * 0.5f > stage_->__size().y)
	//	{
	//		player_->HitStage(D3DXVECTOR2(player_->__position().x,stage_->__size().y - player_->__size().y * 0.5f),true);
	//	}
	//
	//	if(player_->__position().x + player_->__size().x * 0.5f > stage_->__size().x)
	//	{
	//		player_->HitStage(D3DXVECTOR2(stage_->__size().x - player_->__size().x * 0.5f,player_->__position().y),false);
	//	}
	//
	//	if(player_->__position().x - player_->__size().x * 0.5f < 0.0f)
	//	{
	//		player_->HitStage(D3DXVECTOR2(player_->__size().x * 0.5f,player_->__position().y),false);
	//	}
	//
	//	if(player_->__position().y - player_->__size().y * 0.5f < 0.0f)
	//	{
	//		D3DXVECTOR2 vector = player_->__move();
	//		vector.y *= -1;
	//		player_->ChangeDirection(vector);
	//	}
	//	break;
	//}

}

//=============================================================================
// draw
//=============================================================================
void SceneGame::Draw(void)
{
	stage_manager_->Draw();
	//今のステージ解放
	//switch(current_stage_)
	//{
	//case STAGE_ID_SELECT:
	//	stage_select_->Draw();
	//
	//	break;
	//case STAGE_ID_0:
	//case STAGE_ID_1:
	//case STAGE_ID_2:
	//	// draw stage
	//	stage_->Draw();
	//	map_->Draw();
	//	player_->Draw();
	//	break;
	//}
	//
	//// draw fade
	//fade_->Draw();
}

//=============================================================================
// create factory
//=============================================================================
SceneFactory* SceneGame::CreateFactory(void)const
{
	return new GameFactory();
}

//---------------------------------- EOF --------------------------------------
