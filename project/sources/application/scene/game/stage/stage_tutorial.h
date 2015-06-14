//*****************************************************************************
//
// stage tutorial
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _STAGE_TUTORIAL_H_
#define _STAGE_TUTORIAL_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "stage.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class GamePlayer;
class Map;
class StageOffset;
class ObjectStartPoint;

//*****************************************************************************
// class definition
//*****************************************************************************
class StageTutorial : public Stage
{
public:
	// constructor
	StageTutorial(void);

	// destructor
	virtual ~StageTutorial(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// create factory
	StageFactory* CreateFactory(void)const;

	// accessor

private:
	GamePlayer* game_player_;
	Map* map_;
	StageOffset* stage_offset_;
	u32 time_count_;
	ObjectStartPoint* object_start_point_;
};

#endif	// _STAGE_TUTORIAL_H_

//---------------------------------- EOF --------------------------------------
