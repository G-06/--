//*****************************************************************************
//
// input event buffer
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "input_event_buffer.h"

//=============================================================================
// constructor
//=============================================================================
InputEventBuffer::InputEventBuffer(void)
{
	ZeroMemory(input_event_buffer_,INPUT_EVENT_MAX);
	ZeroMemory(input_event_value_buffer_,INPUT_EVENT_VALUE_MAX);
}

//=============================================================================
// destructor
//=============================================================================
InputEventBuffer::~InputEventBuffer(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool InputEventBuffer::Initialize(void)
{
	ZeroMemory(input_event_buffer_,INPUT_EVENT_MAX);
	ZeroMemory(input_event_value_buffer_,INPUT_EVENT_VALUE_MAX);

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void InputEventBuffer::Uninitialize(void)
{
}

//=============================================================================
// set press
//=============================================================================
void InputEventBuffer::SetPress(const INPUT_EVENT& in_input_event,const bool in_press)
{
	if(in_press)
	{
		input_event_buffer_[in_input_event] |= INPUT_EVENT_BIT_PRESS;
	}
	else
	{
		input_event_buffer_[in_input_event] &= ~INPUT_EVENT_BIT_PRESS;
	}
}

//=============================================================================
// set trigger
//=============================================================================
void InputEventBuffer::SetTrigger(const INPUT_EVENT& in_input_event,const bool in_press)
{
	if(in_press)
	{
		input_event_buffer_[in_input_event] |= INPUT_EVENT_BIT_TRIGGER;
	}
	else
	{
		input_event_buffer_[in_input_event] &= ~INPUT_EVENT_BIT_TRIGGER;
	}
}

//=============================================================================
// set release
//=============================================================================
void InputEventBuffer::SetRelease(const INPUT_EVENT& in_input_event,const bool in_press)
{
	if(in_press)
	{
		input_event_buffer_[in_input_event] |= INPUT_EVENT_BIT_RELEASE;
	}
	else
	{
		input_event_buffer_[in_input_event] &= ~INPUT_EVENT_BIT_RELEASE;
	}
}

//=============================================================================
// set repeat
//=============================================================================
void InputEventBuffer::SetRepeat(const INPUT_EVENT& in_input_event,const bool in_press)
{
	if(in_press)
	{
		input_event_buffer_[in_input_event] |= INPUT_EVENT_BIT_REPEAT;
	}
	else
	{
		input_event_buffer_[in_input_event] &= ~INPUT_EVENT_BIT_REPEAT;
	}
}

//=============================================================================
// check press
//=============================================================================
bool InputEventBuffer::CheckPress(const INPUT_EVENT& in_input_event)const
{
	return (input_event_buffer_[in_input_event] & INPUT_EVENT_BIT_PRESS);
}

//=============================================================================
// check trigger
//=============================================================================
bool InputEventBuffer::CheckTrigger(const INPUT_EVENT& in_input_event)const
{
	return (input_event_buffer_[in_input_event] & INPUT_EVENT_BIT_TRIGGER);
}

//=============================================================================
// check release
//=============================================================================
bool InputEventBuffer::CheckRelease(const INPUT_EVENT& in_input_event)const
{
	return (input_event_buffer_[in_input_event] & INPUT_EVENT_BIT_RELEASE);
}

//=============================================================================
// check repeat
//=============================================================================
bool InputEventBuffer::CheckRepeat(const INPUT_EVENT& in_input_event)const
{
	return (input_event_buffer_[in_input_event] & INPUT_EVENT_BIT_REPEAT);
}

//=============================================================================
// set value
//=============================================================================
void InputEventBuffer::SetValue(const INPUT_EVENT_VALUE& in_input_event_value,const u32& in_value)
{
}

//=============================================================================
// get value
//=============================================================================
s32 InputEventBuffer::GetValue(const INPUT_EVENT_VALUE& in_input_event_value)const
{
	return input_event_value_buffer_[in_input_event_value];
}

//---------------------------------- EOF --------------------------------------
