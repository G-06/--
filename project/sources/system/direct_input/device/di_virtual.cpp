//*****************************************************************************
//
// direct input virtual
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "di_virtual.h"
#include "system/system.h"
#include "../input_event_buffer.h"

//=============================================================================
// constructor
//=============================================================================
DIVirtual::DIVirtual(InputEventBuffer* input_event_buffer)
	:DIDevice(nullptr,nullptr,input_event_buffer)
{
}

//=============================================================================
// destructor
//=============================================================================
DIVirtual::~DIVirtual(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool DIVirtual::Initialize(void)
{
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void DIVirtual::Uninitialize(void)
{
}

//=============================================================================
// update
//=============================================================================
void DIVirtual::Update(void)
{
	u8 key_state[KEY_MAX];
	bool press_key = false;
	bool trigger_key;
	bool release_key;

	for(u32 i = 0;i < KEY_MAX;++i)
	{
		for(auto it = input_event_container_[i].begin();it != input_event_container_[i].end();++it)
		{
			press_key = false;

			if(input_event_buffer_->CheckPress(*it))
			{
				// プレスキーの算出
				press_key = true;
				break;
			}
		}

		// トリガーキーの算出
		trigger_key = (press_key ^ preview_key_[i]) & press_key;

		// リリースキーの算出
		release_key = (press_key ^ preview_key_[i]) & !press_key;

		// プレビューキーの保存
		preview_key_[i] = press_key;

		input_event_buffer_->SetPress(static_cast<INPUT_EVENT>(i + INPUT_EVENT_VIRTUAL_0),press_key);
		input_event_buffer_->SetTrigger(static_cast<INPUT_EVENT>(i + INPUT_EVENT_VIRTUAL_0),trigger_key);
		input_event_buffer_->SetRelease(static_cast<INPUT_EVENT>(i + INPUT_EVENT_VIRTUAL_0),release_key);
	}
}

//=============================================================================
// register
//=============================================================================
bool DIVirtual::Register(const INPUT_EVENT& input_event_virtual,const INPUT_EVENT& input_event)
{
	u32 index = input_event_virtual - INPUT_EVENT_VIRTUAL_0;

	if(index >= 0 && index < KEY_MAX)
	{
		input_event_container_[index].push_back(input_event);
		return true;
	}

	return false;
}

//---------------------------------- EOF --------------------------------------
