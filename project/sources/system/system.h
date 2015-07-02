//*****************************************************************************
//
// system
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include gaurd
//*****************************************************************************
#pragma once
#ifndef _SYSYEM_H_
#define _SYSYEM_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "window/window.h"
#include "directx9/directx9.h"
#include "direct_input/direct_input.h"
#include "xaudio2/xaudio2.h"
#include "../application/object/option/option_data.h"

//*****************************************************************************
// macro definition
//*****************************************************************************
#define GET_SYSTEM System::GetInstance()
#define GET_WINDOW System::GetInstance().__window()
#define GET_DIRECTX9 System::GetInstance().__directx9()
#define GET_DIRECTX9_DEVICE System::GetInstance().__directx9()->__direct3ddevice()
#define GET_DIRECT_INPUT System::GetInstance().__direct_input()
#define GET_XAUDIO2 System::GetInstance().__xaudio2()
#define GET_BGM System::GetInstance().__xaudio2()->__bgm()
#define GET_SE System::GetInstance().__xaudio2()->__se()
#define GET_OPTION_DATA System::GetInstance().__option_data();

//*****************************************************************************
// class definition
//*****************************************************************************
class System
{
public:
	// setup
	static bool Setup(HINSTANCE hinstance);

	// shutdown
	static void Shutdown(void);

	// get instance
	static System& GetInstance(void) { return instance_; }

	// accessor
	Window* __window(void)const { return window_; }
	Directx9* __directx9(void)const { return directx9_; }
	DirectInput* __direct_input(void)const { return direct_input_; }
	XAudio2* __xaudio2(void)const { return xaudio2_; }
	OPTION_DATA* __option_data(void) { return &option_data_; }

	static void __set_current_stage(u32 stage){current_stage_ = stage;};
	static u32 __get_current_stage(void){return current_stage_;};

private:
	System(void);
	System(const System& system);
	virtual ~System(void);

	static System instance_;
	Window* window_;
	Directx9* directx9_;
	DirectInput* direct_input_;
	XAudio2* xaudio2_;
	OPTION_DATA option_data_;
	
	static u32 current_stage_;
};

#endif // _SYSYEM_H_

//---------------------------------- EOF --------------------------------------
