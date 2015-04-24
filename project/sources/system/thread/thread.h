//*****************************************************************************
//
// windows thread
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include gaurd
//*****************************************************************************
#pragma once

#ifndef _THREAD_H_
#define _THREAD_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"

//*****************************************************************************
// class definition
//*****************************************************************************
class Thread : public Basic
{
public:
	// constructor
	Thread(void);

	// destructor
	virtual ~Thread(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// start
	bool Start(void* in_func,void* in_arg);

	// stop
	void Stop(void);

	// wait
	void Wait(void);
private:
	HANDLE handle_;
};

#endif // _THREAD_H_

//---------------------------------- EOF --------------------------------------
