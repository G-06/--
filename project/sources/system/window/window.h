//*****************************************************************************
//
// window
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include gaurd
//*****************************************************************************
#pragma once

#ifndef _WINDOW_H_
#define _WINDOW_H_

//*****************************************************************************
// include
//*****************************************************************************
// common
#include "basic/basic.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Thread;

//*****************************************************************************
// class definition
//*****************************************************************************
class Window : public Basic
{
public:
	enum STATUS
	{
		STATUS_NONE = 0,
		STATUS_RESIZE,
		STATUS_STOP,
	};
protected:
	// constructor
	Window(void);

public:
	// destructor
	virtual ~Window(void);

	// initialize
	virtual bool Initialize(void);

	// uninitialize
	virtual void Uninitialize(void);

	// run
	void Run(void);

	// stop
	void Stop(void);

	// wait
	void Wait(void);

	// set window size
	void SetWindowSize(const u32& in_width,const u32& in_height);

	// accessor
	const HWND& __hwnd(void)const{return hwnd_;}
	const u32& __width(void)const{return width_;}
	const u32& __height(void)const{return height_;}
	HINSTANCE __hinstance(void)const{return hinstance_;}
	const bool __is_loop(void)const{return is_loop_;}
protected:
	WNDCLASSEX wndclassex_;
	std::string caption_name_;
	HWND hwnd_;
	u32 width_;
	u32 height_;
	HINSTANCE hinstance_;

	// wait ready
	void WaitReady(void);
private:
	bool volatile is_loop_;
	bool volatile is_ready_;
	Thread* thread_;

	// window thread
	static void WindowThread(Window* in_window);
};

#endif // _WINDOW_H_

//-----------------------------------EOF---------------------------------------
