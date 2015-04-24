//*****************************************************************************
//
// debug tool
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "debug_tool.h"
#include "system/system.h"

//*****************************************************************************
// static variable
//*****************************************************************************
DebugTool DebugTool::instance_;

//=============================================================================
// constructor
//=============================================================================
DebugTool::DebugTool(void) :
debug_console_(nullptr),
debug_trace_(nullptr),
debug_display_(nullptr),
is_pause_(false),
is_temp_(false)
{
#ifndef _RELEASE
#endif
}

//=============================================================================
// destructor
//=============================================================================
DebugTool::~DebugTool(void)
{
#ifndef _RELEASE
#endif
}

//=============================================================================
// setup
//=============================================================================
bool DebugTool::Setup(void)
{
#ifndef _RELEASE
	// create debug console
	instance_.debug_console_ = new DebugConsole();

	// initialize debug console
	SafeInitialize(instance_.debug_console_);

	// create debug trace
	instance_.debug_trace_ = new DebugTrace();

	// initialize debug trace
	SafeInitialize(instance_.debug_trace_);

	// create debug display
	instance_.debug_display_ = new DebugDisplay();

	// initialize debug display
	SafeInitialize(instance_.debug_display_);
#endif // _RELEASE
	return true;
}

//=============================================================================
// shutdown
//=============================================================================
void DebugTool::Shutdown(void)
{
#ifndef _RELEASE
	// release debug console
	SafeRelease(instance_.debug_console_);

	// release debug trace
	SafeRelease(instance_.debug_trace_);

	// release debug display
	SafeRelease(instance_.debug_display_);
#endif // _RELEASE
}

//=============================================================================
// update
//=============================================================================
void DebugTool::Update(void)
{
#ifndef _RELEASE
	// draw debug console
	debug_console_->Update();

	// draw debug display
	debug_display_->Update();

	is_pause_ = is_temp_;

	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_1))
	{
		is_temp_ ^= true;
	}

	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_2))
	{
		is_pause_ = false;
		is_temp_ = true;
	}

	if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_3))
	{
		is_pause_ = false;
		is_temp_ = true;
	}

#endif // _RELEASE
}

//=============================================================================
// draw
//=============================================================================
void DebugTool::Draw(void)
{
#ifndef _RELEASE
	// draw debug console
	debug_console_->Draw();

	// draw debug display
	debug_display_->Draw();
#endif // _RELEASE
}

//-----------------------------------EOF---------------------------------------
