//*****************************************************************************
//
// system
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "system.h"
#include "window/main_window.h"

System System::instance_;

//=============================================================================
// constructor
//=============================================================================
System::System(void)
{
}

//=============================================================================
// destructor
//=============================================================================
System::~System(void)
{
}

//=============================================================================
// setup
//=============================================================================
bool System::Setup(HINSTANCE hinstance)
{
	timeBeginPeriod(0);

	// create window
	instance_.window_ = new MainWindow(hinstance);

	// initialize window
	if(!SafeInitialize(instance_.window_))
	{
		return false;
	}

	// create directx9
	instance_.directx9_ = new Directx9(instance_.window_);

	// initialize directx9
	if(!SafeInitialize(instance_.directx9_))
	{
		ASSERT("failed initialize directx9");
		return false;
	}

	// create xaudio2
	instance_.xaudio2_ = new XAudio2();

	// initialize xaudio2
	if(!SafeInitialize(instance_.xaudio2_))
	{
		ASSERT("falied initialize xaudio2");
		return false;
	}

	// create direct input
	instance_.direct_input_ = new DirectInput();

	// initialize direct input
	if(!SafeInitialize(instance_.direct_input_))
	{
		ASSERT("failed initialize direct input");
		return false;
	}

	return true;
}

//=============================================================================
// shutdown
//=============================================================================
void System::Shutdown(void)
{
	// release window
	SafeRelease(instance_.window_);

	// release directx9
	SafeRelease(instance_.directx9_);

	// release direct input
	SafeRelease(instance_.direct_input_);

	// release xaudio2
	SafeRelease(instance_.xaudio2_);

	timeEndPeriod(0);
}

//-----------------------------------EOF---------------------------------------
