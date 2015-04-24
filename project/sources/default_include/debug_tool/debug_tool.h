//*****************************************************************************
//
// debug tools
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include gaurd
//*****************************************************************************
#pragma once
#ifndef _DEBUG_TOOL_H_
#define _DEBUG_TOOL_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "debug_console.h"
#include "debug_trace.h"
#include "debug_display.h"
#include "assert.h"

//*****************************************************************************
// macro definition
//*****************************************************************************
#ifndef _RELEASE
#define new                   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define malloc(s)             _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define calloc(c, s)          _calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define realloc(p, s)         _realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _recalloc(p, c, s)    _recalloc_dbg(p, c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _expand(p, s)         _expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif // _RELEASE

#define DEBUG_TOOL DebugTool::GetInstance()

//*****************************************************************************
// class definition
//*****************************************************************************
class DebugTool
{
public:
	static DebugTool& GetInstance(void) { return instance_; }

	// setup
	static bool Setup(void);

	// shutdown
	static void Shutdown(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// accessor
	DebugConsole* __debug_console(void)const { return debug_console_; }
	DebugTrace* __debug_trace(void)const { return debug_trace_; }
	DebugDisplay* __debug_display(void)const { return debug_display_; }
	bool __is_pause(void)const { return is_pause_; }

private:
	DebugTool(void);
	DebugTool(DebugTool& debug_tool);
	virtual ~DebugTool(void);
	static DebugTool instance_;
	DebugConsole* debug_console_;
	DebugTrace* debug_trace_;
	DebugDisplay* debug_display_;
	bool is_pause_;
	bool is_temp_;
};

#endif // _DEBUG_TOOL_H_

//---------------------------------- EOF --------------------------------------
