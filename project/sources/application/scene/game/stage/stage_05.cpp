//*****************************************************************************
//
// stage 5
//
// Author		: kitazawa taichi
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "stage_05.h"
#include "stage_factory.h"
#include "object/map.h"
#include "object/stage_offset.h"
#include "system/system.h"

//*****************************************************************************
// constant definition
//*****************************************************************************

//=============================================================================
// constructor
//=============================================================================
StageFive::StageFive(void)
	:NormalStage(TYPE_STAGE5)
{
}

//=============================================================================
// destructor
//=============================================================================
StageFive::~StageFive(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool StageFive::Initialize(void)
{
	GET_BGM->Play(BGM::BGM_ID_STAGE_05);
	NormalStage::Initialize();

	map_ = new Map();

	if(!SafeInitialize(map_))
	{
		return false;
	}

	map_->LoadFromFile("data/work/standoUp.bin");

	stage_offset_->__stage_size(map_->__size());

	LoadFromFile("data/work/standoUp.csv");

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void StageFive::Uninitialize(void)
{
	NormalStage::Uninitialize();
}

//=============================================================================
// update
//=============================================================================
void StageFive::Update(void)
{
	NormalStage::Update();
}

//=============================================================================
// draw
//=============================================================================
void StageFive::Draw(void)
{
	NormalStage::Draw();
}

//=============================================================================
// create factory
//=============================================================================
StageFactory* StageFive::CreateFactory(void)const
{
	return new StageFiveFactory();
}

//---------------------------------- EOF --------------------------------------
