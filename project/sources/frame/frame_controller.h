//*****************************************************************************
//
// frame controller
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _FRAME_CONTROLLER_H_
#define _FRAME_CONTROLLER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Timer;

//*****************************************************************************
// class definition
//*****************************************************************************
class FrameController : public Basic
{
public:
	// constructor
	FrameController(void);

	// destructor
	virtual ~FrameController(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// wait
	void Wait(void);

	// accessor
	const u32& __max_frame(void)const { return max_frame_; }
	void __max_frame(const u32& max_frame) { if(max_frame != 0) { max_frame_ = max_frame; frame_time_ = 1000 / max_frame; } }
	const u32& __fps(void)const { return fps_; }

private:
	static const u32 DEFAULT_MAX_FRAME;
	u32 max_frame_;
	u32 fps_;
	u32 frame_time_;
	u32 frame_count_;
	u32 sum_time_;
	Timer* timer_;

};

#endif	// _FRAME_H_

//---------------------------------- EOF --------------------------------------
