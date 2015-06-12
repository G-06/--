//*****************************************************************************
//
// stage select
//
// Author		: kitazawa taichi
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "stage_select.h"
#include "object/stage_select/select_bg.h"
#include "object/stage_region.h"
#include "object/stage_select/select_arrow.h"
#include "render/sprite.h"
#include "system/system.h"
#include "scene/game/scene_game.h"
#include "stage_factory.h"

//*****************************************************************************
// constant definition
//*****************************************************************************

//=============================================================================
// constructor
//=============================================================================
StageSelect::StageSelect(void)
	:Stage(TYPE_SELECT)
{
}

//=============================================================================
// destructor
//=============================================================================
StageSelect::~StageSelect(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool StageSelect::Initialize(void)
{
	//背景
	select_bg_ = new SelectBg();
	if(!SafeInitialize(select_bg_))
	{
		return false;
	}

	//ブルーニャス

	select_arrow_ = new SelectArrow();
	if(!SafeInitialize(select_arrow_))
	{
		return false;
	}


	//セレクト枠xステージ数
	for(u32 i=0;i<(TYPE_MAX - 1);i++)
	{
		//まとまりを作る
		regions_[i] = new StageRegion();
		if(!SafeInitialize(regions_[i]))
		{
			return false;
		}
		//まとまりにステージ名を与える
		regions_[i]->__set_stage_id(i);
		regions_[i]->__set_region_distpos(D3DXVECTOR2(i*600.0f,0.0f));
	}

	regions_[0]->__set_time(0);

	current_stage_ = 0;

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void StageSelect::Uninitialize(void)
{
	SafeRelease(select_bg_);
	SafeRelease(select_arrow_);

	for(u32 i=0;i<(TYPE_MAX - 1);i++)
	{
		SafeRelease(regions_[i]);
	}
}

//=============================================================================
// update
//=============================================================================
void StageSelect::Update(void)
{
	if(current_stage_ !=2)
	{
		if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_RIGHT))
		{
			for(u32 i=0;i<(TYPE_MAX - 1);i++)
			{
				regions_[i]->__set_region_distpos(D3DXVECTOR2(-600.0f,0.0f));
			}
			current_stage_++;
		}
	}

	if(current_stage_!=0)
	{
		if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_LEFT))
		{
			for(u32 i=0;i<(TYPE_MAX - 1);i++)
			{
				regions_[i]->__set_region_distpos(D3DXVECTOR2(600.0f,0.0f));
			}
			current_stage_--;
		}
	}

	if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_RETURN))
	{
		//決定を押されたとき
		//next_stage_factory_ = new 
		//SceneGame::__next_stage(STAGE_ID_1);
	}

	select_arrow_->__set_stage_id(current_stage_);
	select_arrow_ ->Update();

	//まとまりに更新をかける
	for(u32 i=0;i<(TYPE_MAX - 1);i++)
	{
		regions_[i]->Update();
	}
}

//=============================================================================
// draw
//=============================================================================
void StageSelect::Draw(void)
{
	select_bg_->Draw();

	for(u32 i=0;i<(TYPE_MAX - 1);i++)
	{
		regions_[i]->Draw();
	}

	select_arrow_->Draw();
}

//=============================================================================
// create factory
//=============================================================================
StageFactory* StageSelect::CreateFactory(void)const
{
	return new SelectFactory();
}

//---------------------------------- EOF --------------------------------------
