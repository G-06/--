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

//*****************************************************************************
// macro definition
//*****************************************************************************
#define GET_SYSTEM System::GetInstance()
#define GET_DIRECTX9 System::GetInstance().__directx9()
#define GET_DIRECTX9_DEVICE System::GetInstance().__directx9()->__direct3ddevice()
#define GET_DIRECT_INPUT System::GetInstance().__direct_input()

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
private:
	System(void);
	System(const System& system);
	virtual ~System(void);

	static System instance_;
	Window* window_;
	Directx9* directx9_;
	DirectInput* direct_input_;
};

#endif // _SYSYEM_H_

//---------------------------------- EOF --------------------------------------
