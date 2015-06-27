//*****************************************************************************
//
// stage factory
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _STAGE_FACTORY_H_
#define _STAGE_FACTORY_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "stage.h"
#include "stage_select.h"
#include "stage_tutorial.h"
#include "stage_01.h"
#include "stage_02.h"
#include "stage_03.h"
#include "stage_04.h"
#include "stage_05.h"
#include "stage_06.h"
#include "stage_07.h"
#include "stage_08.h"
#include "stage_09.h"
#include "stage_10.h"

//*****************************************************************************
// class definition
//*****************************************************************************
class StageFactory
{
public:
	// constructor
	StageFactory(const Stage::TYPE& type) { type_ = type; }

	// destructor
	virtual ~StageFactory(void) {}

	// create
	virtual Stage* Create(void)const = 0;

	// accessor
	const Stage::TYPE& __type(void)const { return type_; }
private:
	Stage::TYPE type_;
};

//*****************************************************************************
// select factory
//*****************************************************************************
class SelectFactory : public StageFactory
{
public:
	// constructor
	SelectFactory(void) : StageFactory(Stage::TYPE_SELECT) {}

	// destructor
	virtual ~SelectFactory(void) {}

	// create
	Stage* Create(void)const { return new StageSelect(); }
};


//*****************************************************************************
// tutorial factory
//*****************************************************************************
class TutorialFactory : public StageFactory
{
public:
	// constructor
	TutorialFactory(void) : StageFactory(Stage::TYPE_TUTORIAL) {}

	// destructor
	virtual ~TutorialFactory(void) {}

	// create
	Stage* Create(void)const { return new StageTutorial(); }
};

//*****************************************************************************
// stage1 factory
//*****************************************************************************
class StageOneFactory : public StageFactory
{
public:
	// constructor
	StageOneFactory(void) : StageFactory(Stage::TYPE_STAGE1) {}

	// destructor
	virtual ~StageOneFactory(void) {}

	// create
	Stage* Create(void)const { return new StageOne(); }
};

//*****************************************************************************
// stage2 factory
//*****************************************************************************
class StageTwoFactory : public StageFactory
{
public:
	// constructor
	StageTwoFactory(void) : StageFactory(Stage::TYPE_STAGE2) {}

	// destructor
	virtual ~StageTwoFactory(void) {}

	// create
	Stage* Create(void)const { return new StageTwo(); }
};

//*****************************************************************************
// stage3 factory
//*****************************************************************************
class StageThreeFactory : public StageFactory
{
public:
	// constructor
	StageThreeFactory(void) : StageFactory(Stage::TYPE_STAGE3) {}

	// destructor
	virtual ~StageThreeFactory(void) {}

	// create
	Stage* Create(void)const { return new StageThree(); }
};

//*****************************************************************************
// stage4 factory
//*****************************************************************************
class StageFourFactory : public StageFactory
{
public:
	// constructor
	StageFourFactory(void) : StageFactory(Stage::TYPE_STAGE4) {}

	// destructor
	virtual ~StageFourFactory(void) {}

	// create
	Stage* Create(void)const { return new StageFour(); }
};

//*****************************************************************************
// stage5 factory
//*****************************************************************************
class StageFiveFactory : public StageFactory
{
public:
	// constructor
	StageFiveFactory(void) : StageFactory(Stage::TYPE_STAGE5) {}

	// destructor
	virtual ~StageFiveFactory(void) {}

	// create
	Stage* Create(void)const { return new StageFive(); }
};

//*****************************************************************************
// stage6 factory
//*****************************************************************************
class StageSixFactory : public StageFactory
{
public:
	// constructor
	StageSixFactory(void) : StageFactory(Stage::TYPE_STAGE6) {}

	// destructor
	virtual ~StageSixFactory(void) {}

	// create
	Stage* Create(void)const { return new StageSix(); }
};

//*****************************************************************************
// stage7 factory
//*****************************************************************************
class StageSevenFactory : public StageFactory
{
public:
	// constructor
	StageSevenFactory(void) : StageFactory(Stage::TYPE_STAGE7) {}

	// destructor
	virtual ~StageSevenFactory(void) {}

	// create
	Stage* Create(void)const { return new StageSeven(); }
};

//*****************************************************************************
// stage8 factory
//*****************************************************************************
class StageEightFactory : public StageFactory
{
public:
	// constructor
	StageEightFactory(void) : StageFactory(Stage::TYPE_STAGE8) {}

	// destructor
	virtual ~StageEightFactory(void) {}

	// create
	Stage* Create(void)const { return new StageEight(); }
};

//*****************************************************************************
// stage9 factory
//*****************************************************************************
class StageNineFactory : public StageFactory
{
public:
	// constructor
	StageNineFactory(void) : StageFactory(Stage::TYPE_STAGE9) {}

	// destructor
	virtual ~StageNineFactory(void) {}

	// create
	Stage* Create(void)const { return new StageNine(); }
};

//*****************************************************************************
// stage10 factory
//*****************************************************************************
class StageTenFactory : public StageFactory
{
public:
	// constructor
	StageTenFactory(void) : StageFactory(Stage::TYPE_STAGE10) {}

	// destructor
	virtual ~StageTenFactory(void) {}

	// create
	Stage* Create(void)const { return new StageTen(); }
};

//*****************************************************************************
// game factory
//*****************************************************************************
//class GameFactory : public StageFactory
//{
//public:
//	// constructor
//	GameFactory(void) : StageFactory(Stage::TYPE_000) {}
//
//	// destructor
//	virtual ~GameFactory(void) {}
//
//	// create
//	Stage* Create(void)const { return new StageGame(); }
//};

#endif	// _STAGE_FACTORY_H_

//---------------------------------- EOF --------------------------------------
