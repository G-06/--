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
#include "stage_select/select_bg.h"
#include "stage_region.h"
#include "render/sprite.h"
#include "system/system.h"
#include "scene/game/scene_game.h"
#include "stage_select/select_arrow.h"

//*****************************************************************************
// constant definition
//*****************************************************************************

//=============================================================================
// constructor
//=============================================================================
StageSelect::StageSelect(void)
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
	//�w�i
	select_bg_ = new SelectBg();
	if(!SafeInitialize(select_bg_))
	{
		return false;
	}

	//�u���[�j���X

	select_arrow_ = new SelectArrow();
	if(!SafeInitialize(select_arrow_))
	{
		return false;
	}


	//�Z���N�g�gx�X�e�[�W��
	for(u32 i=0;i<STAGE_ID_MAX;i++)
	{
		//�܂Ƃ܂�����
		regions_[i] = new StageRegion();
		if(!SafeInitialize(regions_[i]))
		{
			return false;
		}
		//�܂Ƃ܂�ɃX�e�[�W����^����
		regions_[i]->__set_stage_id((STAGE_ID)i);
		regions_[i]->__set_region_distpos(D3DXVECTOR2(i*600.0f,0.0f));
	}

	regions_[0]->__set_time(0);
	regions_[1]->__set_time(234);
	regions_[2]->__set_time(181);

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

	for(u32 i=0;i<STAGE_ID_MAX;i++)
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
			for(u32 i=0;i<STAGE_ID_MAX;i++)
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
			for(u32 i=0;i<STAGE_ID_MAX;i++)
			{
				regions_[i]->__set_region_distpos(D3DXVECTOR2(600.0f,0.0f));
			}
			current_stage_--;
		}
	}



	if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_RETURN))
	{
		//����������ꂽ�Ƃ�
		SceneGame::__next_stage(STAGE_ID_1);
	}

	select_arrow_->__set_stage_id((STAGE_ID)current_stage_);
	select_arrow_ ->Update();

	//�܂Ƃ܂�ɍX�V��������
	for(u32 i=0;i<STAGE_ID_MAX;i++)
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

	for(u32 i=0;i<STAGE_ID_MAX;i++)
	{
		regions_[i]->Draw();
	}

	select_arrow_->Draw();
}

//---------------------------------- EOF --------------------------------------
