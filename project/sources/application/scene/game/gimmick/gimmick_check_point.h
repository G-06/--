//*****************************************************************************
//
// gimmick check point
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _GIMMICK_CHECK_POINT_H_
#define _GIMMICK_CHECK_POINT_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "gimmick.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class ObjectCheckPoint;

//*****************************************************************************
// class definition
//*****************************************************************************
class GimmickCheckPoint : public Gimmick
{
public:
	struct DATA
	{
		u32 _priority;
		bool _hit;
	};

	// constructor
	GimmickCheckPoint(void);

	// destructor
	virtual ~GimmickCheckPoint(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	void* GetPointer(void);

	// accessor
	u32 __priority(void)const { return data_._priority; }
	void __priority(u32 priority) { data_._priority = priority; }

private:
	ObjectCheckPoint* object_check_point_;
	DATA data_;
	bool onece_;
};

#endif	// _GIMMICK_CHECK_POINT_H_

//---------------------------------- EOF --------------------------------------
