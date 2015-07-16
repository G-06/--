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
	NormalStage::Initialize();

	map_ = new Map();

	if(!SafeInitialize(map_))
	{
		return false;
	}

	map_->LoadFromFile("data/work/healtest.bin");

	stage_offset_->__stage_size(map_->__size());

	LoadFromFile("data/work/healtest.csv");

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
