//*****************************************************************************
//
// gimmick goal point
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _GIMMICK_GOAL_POINT_H_
#define _GIMMICK_GOAL_POINT_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "gimmick.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class ObjectGoalPoint;

//*****************************************************************************
// class definition
//*****************************************************************************
class GimmickGoalPoint : public Gimmick
{
public:
	// constructor
	GimmickGoalPoint(void);

	// destructor
	virtual ~GimmickGoalPoint(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// accessor

private:
	ObjectGoalPoint* object_goal_point_;
	f32 rotation_;
};

#endif	// _GIMMICK_GOAL_POINT_H_

//---------------------------------- EOF --------------------------------------
