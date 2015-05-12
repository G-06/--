//*****************************************************************************
//
// direct input
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "direct_input.h"
#include "input_event_buffer.h"
#include "device/di_device.h"
#include "device/di_keyboard.h"
#include "device/di_mouse.h"
#include "device/di_virtual.h"
#include "system/system.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const s8* DirectInput::SYSTEM_FILE_NAME = "resources/system/input.bin";

//=============================================================================
// constructor
//=============================================================================
DirectInput::DirectInput(void)
{
}

//=============================================================================
// destructor
//=============================================================================
DirectInput::~DirectInput(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool DirectInput::Initialize(void)
{
	window_ = GET_SYSTEM.__window();

	input_event_buffer_ = new InputEventBuffer();

	// create direct input
	DirectInput8Create(window_->__hinstance(),DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&direct_input_,NULL);

	// create direct input keyboard
	DIKeyboard* di_keyboard = new DIKeyboard(direct_input_,window_,input_event_buffer_);

	// push direct input keyboard to device list
	device_list_.push_back(di_keyboard);

	// create direct input keyboard
	DIMouse* di_mouse = new DIMouse(direct_input_,window_,input_event_buffer_);

	// push direct input mouse to device list
	device_list_.push_back(di_mouse);

	// create direct input keyboard
	di_virtual_ = new DIVirtual(input_event_buffer_);

	// push direct input virtual to device list
	device_list_.push_back(di_virtual_);

	// load input file
	di_virtual_->Load(SYSTEM_FILE_NAME);

	for(auto it = device_list_.begin();it != device_list_.end();++it)
	{
		if(!SafeInitialize(*it))
		{
			return false;
		}
	}

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void DirectInput::Uninitialize(void)
{
	for(auto it = device_list_.begin();it != device_list_.end();++it)
	{
		SafeRelease(*it);
	}

	SafeRelease(input_event_buffer_);
}

//=============================================================================
// update
//=============================================================================
void DirectInput::Update(void)
{
	for(auto it = device_list_.begin();it != device_list_.end();++it)
	{
		(*it)->Update();
	}
}

//=============================================================================
// check press
//=============================================================================
bool DirectInput::CheckPress(const INPUT_EVENT& input_event)
{
	return input_event_buffer_->CheckPress(input_event);
}

//=============================================================================
// check trigger
//=============================================================================
bool DirectInput::CheckTrigger(const INPUT_EVENT& input_event)
{
	return input_event_buffer_->CheckTrigger(input_event);
}

//=============================================================================
// check release
//=============================================================================
bool DirectInput::CheckRelease(const INPUT_EVENT& input_event)
{
	return input_event_buffer_->CheckRelease(input_event);
}

//=============================================================================
// check repeat
//=============================================================================
bool DirectInput::CheckRepeat(const INPUT_EVENT& input_event)
{
	return input_event_buffer_->CheckRepeat(input_event);
}

//=============================================================================
// get value
//=============================================================================
s32 DirectInput::GetValue(const INPUT_EVENT_VALUE& input_event_value)
{
	return input_event_buffer_->GetValue(input_event_value);
}

//=============================================================================
// register input event vertual
//=============================================================================
bool DirectInput::RegisterInputEventVertual(const INPUT_EVENT& input_event_virtual,const INPUT_EVENT& input_event)
{
	return di_virtual_->Register(input_event_virtual,input_event);
}

//=============================================================================
// save input event vertual
//=============================================================================
void DirectInput::SaveInputEventVertual(void)
{
	di_virtual_->Save(SYSTEM_FILE_NAME);
}

//---------------------------------- EOF --------------------------------------
