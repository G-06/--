//*****************************************************************************
//
// debug console
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include gaurd
//*****************************************************************************
#pragma once
#ifndef _DEBUG_CONSOLE_H_
#define _DEBUG_CONSOLE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"

//*****************************************************************************
// class definition
//*****************************************************************************
class DebugConsole : public Basic
{
public:
	// constructor
	DebugConsole(void);

	// destructor
	virtual ~DebugConsole(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// print
	void Print(const s8* format,...);

	// show
	void Show(void);

	// hide
	void Hide(void);

	// switch window
	void SwitchWindow(void);

private:
	static const s8* CAPTION;
	static const int STRING_MAX = 1024;
	HWND hwnd_;
	s8 string_[STRING_MAX];

	u32 console_;
	bool is_show_;
};

#endif // _DEBUG_CONSOLE_H_

//---------------------------------- EOF --------------------------------------
