//*****************************************************************************
//
// stage 9
//
// Author		: kitazawa taichi
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "stage_09.h"
#include "stage_factory.h"
#include "object/map.h"
#include "object/stage_offset.h"

//*****************************************************************************
// constant definition
//*****************************************************************************

//=============================================================================
// constructor
//=============================================================================
StageNine::StageNine(void)
	:NormalStage(TYPE_STAGE9)
{
}

//=============================================================================
// destructor
//=============================================================================
StageNine::~StageNine(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool StageNine::Initialize(void)
{
	NormalStage::Initialize();

	map_ = new Map();

	if(!SafeInitialize(map_))
	{
		return false;
	}

	map_->LoadFromFile("data/work/tst.bin");

	stage_offset_->__stage_size(map_->__size());

	LoadFromFile("data/work/tst.csv");

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void StageNine::Uninitialize(void)
{
	NormalStage::Uninitialize();
}

//=============================================================================
// update
//=============================================================================
void StageNine::Update(void)
{
	NormalStage::Update();
}

//=============================================================================
// draw
//=============================================================================
void StageNine::Draw(void)
{
	NormalStage::Draw();
}

//=============================================================================
// create factory
//=============================================================================
StageFactory* StageNine::CreateFactory(void)const
{
	return new StageNineFactory();
}

//---------------------------------- EOF --------------------------------------
