//*****************************************************************************
//
// direct input mouse
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include gaurd
//*****************************************************************************
#pragma once
#ifndef _DI_MOUSE_H_
#define _DI_MOUSE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "di_device.h"

//*****************************************************************************
// class definition
//*****************************************************************************
class DIMouse : public DIDevice
{
public:
	// constructor
	DIMouse(LPDIRECTINPUT8 direct_input,Window* window,InputEventBuffer* input_event_buffer);

	// destructor
	virtual ~DIMouse(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

private:
	static const u8 PUSH_BIT = 0x80;
	static const u16 KEY_MAX = 3;
	bool preview_key_[KEY_MAX];
};

#endif // _DI_MOUSE_H_

//---------------------------------- EOF --------------------------------------
