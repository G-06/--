//*****************************************************************************
//
// direct input virtual
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include gaurd
//*****************************************************************************
#pragma once
#ifndef _DI_VIRTUAL_H_
#define _DI_VIRTUAL_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "di_device.h"
#include "../input_alias.h"

//*****************************************************************************
// class definition
//*****************************************************************************
class DIVirtual : public DIDevice
{
public:
	// constructor
	DIVirtual(InputEventBuffer* input_event_buffer);

	// destructor
	virtual ~DIVirtual(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);
	
	// update
	void Update(void);

	// register
	bool Register(const INPUT_EVENT& input_event_virtual,const INPUT_EVENT& input_event);

private:
	static const u16 KEY_MAX = INPUT_EVENT_VIRTUAL_15 - INPUT_EVENT_VIRTUAL_0;
	bool preview_key_[KEY_MAX];
	std::list<INPUT_EVENT> input_event_container_[KEY_MAX];
};

#endif // _DI_VIRTUAL_H_

//---------------------------------- EOF --------------------------------------
