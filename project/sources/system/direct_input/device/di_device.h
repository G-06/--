//*****************************************************************************
//
// direct input device
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include gaurd
//*****************************************************************************
#pragma once
#ifndef _DI_DEVICE_H_
#define _DI_DEVICE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class InputEventBuffer;
class Window;

//*****************************************************************************
// class definition
//*****************************************************************************
class DIDevice : public Basic
{
public:
	// constructor
	DIDevice(LPDIRECTINPUT8 in_direct_input,Window* in_window,InputEventBuffer* in_input_event_buffer);

	// destructor
	virtual ~DIDevice(void);

	// initialize
	virtual bool Initialize(void);

	// uninitialize
	virtual void Uninitialize(void);

	// update
	virtual void Update(void) = 0;

protected:
	LPDIRECTINPUT8 direct_input_;
	Window* window_;
	InputEventBuffer* input_event_buffer_;
	LPDIRECTINPUTDEVICE8 direct_input_device_;
};

#endif // _DI_DEVICE_H_

//---------------------------------- EOF --------------------------------------
