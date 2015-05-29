//*****************************************************************************
//
// direct input device
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "di_device.h"
#include "../input_event_buffer.h"

//=============================================================================
// constructor
//=============================================================================
DIDevice::DIDevice(LPDIRECTINPUT8 direct_input,Window* window,InputEventBuffer* input_event_buffer) :
direct_input_(nullptr),
window_(nullptr),
input_event_buffer_(nullptr),
direct_input_device_(nullptr)
{
	direct_input_ = direct_input;
	window_ = window;
	input_event_buffer_ = input_event_buffer;
}

//=============================================================================
// destructor
//=============================================================================
DIDevice::~DIDevice(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool DIDevice::Initialize(void)
{
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void DIDevice::Uninitialize(void)
{
	if(direct_input_device_ != nullptr)
	{
		direct_input_device_->Unacquire();
		direct_input_device_->Release();
		direct_input_device_ = nullptr;
	}
}

//---------------------------------- EOF --------------------------------------
