//*****************************************************************************
//
// timer
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once

#ifndef _TIMER_H_
#define _TIMER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"

//*****************************************************************************
// class definition
//*****************************************************************************
class Timer : public Basic
{
public:
	// constructor
	Timer(void);

	// destructor
	virtual ~Timer(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// start
	void Start(void);

	// stop
	u32 Stop(void);

	// pause
	u32 Pause(void);

	// reset
	void Reset(void);

	// get time
	u32 GetTime(void);
private:
	bool is_start_;
	bool is_pause_;
	u32 start_time_;
	u32 current_time_;
	u32 pause_time_;
};

#endif	// _TIMER_H_

//---------------------------------- EOF --------------------------------------
