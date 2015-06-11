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
#include "render/fade.h"


STAGE_ID SceneGame:: next_stage_;		// 今いるステージ（ステージ選択含む）


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
	// 今いるステージを設定
	current_stage_ = STAGE_ID_MAX;
	//次行くステージ
	__next_stage(STAGE_ID_SELECT);

	// create fade
	fade_ = new Fade();
	// initialize fade
	fade_->Initialize();



	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void SceneGame::Uninitialize(void)
{
	//今のステージ解放
	switch(current_stage_)
	{
	case STAGE_ID_SELECT:
		SafeRelease(stage_select_);

		break;
	case STAGE_ID_0:
	case STAGE_ID_1:
	case STAGE_ID_2:
		// release stage offset
		SafeRelease(stage_offset_);
		// release stage
		SafeRelease(stage_);
		SafeRelease(player_);
		break;
	}

	// release fade
	SafeRelease(fade_);

	SafeDelete(next_scene_factory_);
}

//=============================================================================
// update
//=============================================================================
void SceneGame::Update(void)
{
	//ステージの切り替え 
	if(next_stage_ != STAGE_ID_MAX)
	{
		if(fade_ ->__type() == Fade::TYPE_NONE)
		{
			// fade out
			fade_->Start(Fade::TYPE_OUT);
		}
		ChangeNextStage();
	}

	if(fade_ ->__type() == Fade::TYPE_FADE)
	{
		fade_->Start(Fade::TYPE_IN);
	}


	// update fade
	fade_->Update();


	//今のステージ更新
	switch(current_stage_)
	{
	case STAGE_ID_SELECT:
		stage_select_->Update();

		break;
	case STAGE_ID_0:
	case STAGE_ID_1:
	case STAGE_ID_2:
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
		break;
	}

}

//=============================================================================
// draw
//=============================================================================
void SceneGame::Draw(void)
{
	//今のステージ解放
	switch(current_stage_)
	{
	case STAGE_ID_SELECT:
		stage_select_->Draw();

		break;
	case STAGE_ID_0:
	case STAGE_ID_1:
	case STAGE_ID_2:
		// draw stage
		stage_->Draw();
		player_->Draw();
		break;
	}

	// draw fade
	fade_->Draw();
}

//=============================================================================
// create factory
//=============================================================================
SceneFactory* SceneGame::CreateFactory(void)const
{
	return new GameFactory();
}

//=============================================================================
// ステージの切り替え
//=============================================================================
bool SceneGame::ChangeNextStage(void)
{
	//画面が真っ白になった時
	if(fade_ ->__type() == Fade::TYPE_FADE)
	{
		//今のステージ解放
		switch(current_stage_)
		{
		case STAGE_ID_SELECT:
			SafeRelease(stage_select_);

			break;
		case STAGE_ID_0:
		case STAGE_ID_1:
		case STAGE_ID_2:
			// release stage offset
			SafeRelease(stage_offset_);
			// release stage
			SafeRelease(stage_);
			SafeRelease(player_);

			break;
		}

		//次のステージ初期化
		switch(next_stage_)
		{
		case STAGE_ID_SELECT:
			//ステージセレクトを作る
			stage_select_ = new StageSelect();
			if(!SafeInitialize(stage_select_))
			{
				return false;
			}

			break;
		case STAGE_ID_0:
		case STAGE_ID_1:
		case STAGE_ID_2:
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

			stage_offset_->__screen_size(D3DXVECTOR2((f32)GET_WINDOW->__width(),(f32)GET_WINDOW->__height()));
			stage_offset_->__stage_size(stage_->__size());

			break;
		}

		//次のステージを今に
		current_stage_ = next_stage_;
		next_stage_ = STAGE_ID_MAX;
	}
	return true;
}


//---------------------------------- EOF --------------------------------------
