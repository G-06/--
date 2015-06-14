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
#include "application/object/stage_select/select_bg.h"
#include "application/object/stage_region.h"
#include "render/sprite.h"
#include "system/system.h"
#include "scene/game/scene_game.h"
#include "application/object/stage_select/select_arrow.h"
#include "application/object/record.h"
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

	//矢印
	select_arrow_ = new SelectArrow();
	if(!SafeInitialize(select_arrow_))
	{
		return false;
	}

	////セレクト枠xステージ数
	for(u32 i=0;i<TYPE_MAX-1;i++)
	{
		regions_[i].region_ = new StageRegion();
		regions_[i].region_->Initialize();
		regions_[i].position_ = D3DXVECTOR2(i*1098.0f,0.0f);
		regions_[i].region_->__set_position(regions_[i].position_);
		regions_[i].type_ = ((TYPE)(i+1));
		regions_[i].region_->__set_stage_id(regions_[i].type_);
		regions_[i].region_->__set_time(181);
	}

	current_stage_ = TYPE_TUTORIAL;

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void StageSelect::Uninitialize(void)
{
	SafeRelease(select_bg_);
	SafeRelease(select_arrow_);	

	for(u32 i=0;i<TYPE_MAX-1;i++)
	{
		SafeRelease(regions_[i].region_);
	}
}

//=============================================================================
// update
//=============================================================================
void StageSelect::Update(void)
{

	if(current_stage_ !=TYPE_MAX-1)
	{
		if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_RIGHT))
		{
			for(u32 i=0;i<TYPE_MAX-1;i++)
			{
				regions_[i].region_->__set_region_distpos(D3DXVECTOR2(-1098.0f,0.0f));
				select_bg_->__set_distmove(-0.5f);
			}
			current_stage_++;
		}
	}

	if(current_stage_!=TYPE_TUTORIAL)
	{
		if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_LEFT))
		{
			for(u32 i=0;i<TYPE_MAX-1;i++)
			{
				regions_[i].region_->__set_region_distpos(D3DXVECTOR2(1098.0f,0.0f));
				select_bg_->__set_distmove(0.5f);
			}
			current_stage_--;
		}
	}

	//if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_RETURN))
	//{
	//	//決定を押されたとき
	//	SceneGame::__next_stage(STAGE_ID_1);
	//}

	select_bg_->Update();
	select_arrow_->__set_stage_id((Stage::TYPE)current_stage_);
	select_arrow_ ->Update();

	//まとまりに更新をかける
	for(u32 i=0;i<TYPE_MAX-1;i++)
	{
		regions_[i].region_->Update();
	}

	int a = 0;
}

//=============================================================================
// draw
//=============================================================================
void StageSelect::Draw(void)
{
	select_bg_->Draw();

	for(u32 i=0;i<TYPE_MAX-1;i++)
	{
		regions_[i].region_->Draw();
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
