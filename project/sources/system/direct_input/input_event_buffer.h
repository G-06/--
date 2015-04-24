//*****************************************************************************
//
// input event buffer
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include gaurd
//*****************************************************************************
#pragma once
#ifndef _INPUT_EVENT_BUFFER_H_
#define _INPUT_EVENT_BUFFER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "input_alias.h"

//*****************************************************************************
// class definition
//*****************************************************************************
class InputEventBuffer : public Basic
{
public:
	// constructor
	InputEventBuffer(void);

	// destructor
	virtual ~InputEventBuffer(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// set press
	void SetPress(const INPUT_EVENT& in_input_event,const bool in_press);

	// set trigger
	void SetTrigger(const INPUT_EVENT& in_input_event,const bool in_press);

	// set release
	void SetRelease(const INPUT_EVENT& in_input_event,const bool in_press);

	// set repeat
	void SetRepeat(const INPUT_EVENT& in_input_event,const bool in_press);

	// check press
	bool CheckPress(const INPUT_EVENT& in_input_event)const;

	// check trigger
	bool CheckTrigger(const INPUT_EVENT& in_input_event)const;

	// check release
	bool CheckRelease(const INPUT_EVENT& in_input_event)const;

	// check repeat
	bool CheckRepeat(const INPUT_EVENT& in_input_event)const;

	// set value
	void SetValue(const INPUT_EVENT_VALUE& in_input_event_value,const u32& in_value);

	// get value
	s32 GetValue(const INPUT_EVENT_VALUE& in_input_event_value)const;
private:
	enum INPUT_EVENT_BIT
	{
		INPUT_EVENT_BIT_PRESS   = 0x01,
		INPUT_EVENT_BIT_TRIGGER = 0x02,
		INPUT_EVENT_BIT_RELEASE = 0x04,
		INPUT_EVENT_BIT_REPEAT  = 0x08,
		INPUT_EVENT_BIT_ALL     = 0xFF,
	};
	u8 input_event_buffer_[INPUT_EVENT_MAX];
	s32 input_event_value_buffer_[INPUT_EVENT_VALUE_MAX];
};

#endif // _INPUT_EVENT_BUFFER_H_

//-----------------------------------EOF---------------------------------------
