//*****************************************************************************
//
// main window
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include gaurd
//*****************************************************************************
#pragma once

#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "window.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Window;

//*****************************************************************************
// class definition
//*****************************************************************************
class MainWindow : public Window
{
public:
	// constructor
	MainWindow(HINSTANCE in_hinstance);

	// destructor
	virtual ~MainWindow(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);
private:
	static const u32 DEFAULT_WIDTH;
	static const u32 DEFAULT_HEIGHT;
	static const s8* CLASS_NAME;
	static const s8* CAPTION_NAME;

	// window procedure
	static LRESULT CALLBACK WindowProcedure(HWND in_hwnd, UINT in_message, WPARAM in_wparam, LPARAM in_lparam);
};

#endif // _MAIN_WINDOW_H_

//-----------------------------------EOF---------------------------------------
