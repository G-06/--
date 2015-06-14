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
