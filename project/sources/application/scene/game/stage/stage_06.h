//*****************************************************************************
//
// stage 6
//
// Author		: kitazawa taichi
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _STAGE_SIX_H_
#define _STAGE_SIX_H_

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
class StageSix : public NormalStage
{
public:
	// constructor
	StageSix(void);

	// destructor
	virtual ~StageSix(void);

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

#endif	// _stage 6_H_

//---------------------------------- EOF --------------------------------------
