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
#include "normal_stage.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************

//*****************************************************************************
// class definition
//*****************************************************************************
class StageTutorial : public NormalStage
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

};

#endif	// _STAGE_TUTORIAL_H_

//---------------------------------- EOF --------------------------------------
