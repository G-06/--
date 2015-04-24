//*****************************************************************************
//
// direct input keyboard
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include gaurd
//*****************************************************************************
#pragma once
#ifndef _DI_KEYBOARD_H_
#define _DI_KEYBOARD_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "di_device.h"

//*****************************************************************************
// class definition
//*****************************************************************************
class DIKeyboard : public DIDevice
{
public:
	// constructor
	DIKeyboard(LPDIRECTINPUT8 direct_input,Window* window,InputEventBuffer* input_event_buffer);

	// destructor
	virtual ~DIKeyboard(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);
	
	// update
	void Update(void);

private:
	static const u16 KEY_MAX = 256;
	bool preview_key_[KEY_MAX];

};

#endif // _DI_KEYBOARD_H_

//---------------------------------- EOF --------------------------------------
