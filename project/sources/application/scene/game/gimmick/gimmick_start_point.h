//*****************************************************************************
//
// gimmick start point
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _GIMMICK_START_POINT_H_
#define _GIMMICK_START_POINT_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "gimmick.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class ObjectStartPoint;

//*****************************************************************************
// class definition
//*****************************************************************************
class GimmickStartPoint : public Gimmick
{
public:
	// constructor
	GimmickStartPoint(void);

	// destructor
	virtual ~GimmickStartPoint(void);

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
	ObjectStartPoint* object_start_point_;
};

#endif	// _GIMMICK_START_POINT_H_

//---------------------------------- EOF --------------------------------------
