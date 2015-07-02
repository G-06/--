//*****************************************************************************
//
// stage 6
//
// Author		: kitazawa taichi
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "stage_06.h"
#include "stage_factory.h"
#include "object/map.h"
#include "object/stage_offset.h"

//*****************************************************************************
// constant definition
//*****************************************************************************

//=============================================================================
// constructor
//=============================================================================
StageSix::StageSix(void)
	:NormalStage(TYPE_TUTORIAL)
{
}

//=============================================================================
// destructor
//=============================================================================
StageSix::~StageSix(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool StageSix::Initialize(void)
{
	NormalStage::Initialize();

	map_ = new Map();

	if(!SafeInitialize(map_))
	{
		return false;
	}

	map_->LoadFromFile("data/map/stage1.bin");

	stage_offset_->__stage_size(map_->__size());

	LoadFromFile("data/script/stage1.csv");

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void StageSix::Uninitialize(void)
{
	NormalStage::Uninitialize();
}

//=============================================================================
// update
//=============================================================================
void StageSix::Update(void)
{
	NormalStage::Update();
}

//=============================================================================
// draw
//=============================================================================
void StageSix::Draw(void)
{
	NormalStage::Draw();
}

//=============================================================================
// create factory
//=============================================================================
StageFactory* StageSix::CreateFactory(void)const
{
	return new StageSixFactory();
}

//---------------------------------- EOF --------------------------------------
