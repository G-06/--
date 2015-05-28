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
				// �v���X�L�[�̎Z�o
				press_key = true;
				break;
			}
		}

		// �g���K�[�L�[�̎Z�o
		trigger_key = (press_key ^ preview_key_[i]) & press_key;

		// �����[�X�L�[�̎Z�o
		release_key = (press_key ^ preview_key_[i]) & !press_key;

		// �v���r���[�L�[�̕ۑ�
		preview_key_[i] = press_key;

		input_event_buffer_->SetPress(static_cast<INPUT_EVENT>(i + INPUT_EVENT_VIRTUAL_LEFT),press_key);
		input_event_buffer_->SetTrigger(static_cast<INPUT_EVENT>(i + INPUT_EVENT_VIRTUAL_LEFT),trigger_key);
		input_event_buffer_->SetRelease(static_cast<INPUT_EVENT>(i + INPUT_EVENT_VIRTUAL_LEFT),release_key);
	}
}

//=============================================================================
// register
//=============================================================================
bool DIVirtual::Register(const INPUT_EVENT& input_event_virtual,const INPUT_EVENT& input_event)
{
	u32 index = input_event_virtual - INPUT_EVENT_VIRTUAL_LEFT;

	if(index >= 0 && index < KEY_MAX)
	{
		for(auto it = input_event_container_[index].begin();it != input_event_container_[index].end();++it)
		{
			if(*it == input_event)
			{
				return false;
			}
		}

		input_event_container_[index].push_back(input_event);
		return true;
	}

	return false;
}

//=============================================================================
// unregister
//=============================================================================
void DIVirtual::Unregister(const INPUT_EVENT& input_event_virtual,const INPUT_EVENT& input_event)
{
	u32 index = input_event_virtual - INPUT_EVENT_VIRTUAL_LEFT;

	if(index >= 0 && index < KEY_MAX)
	{
		for(auto it = input_event_container_[index].begin();it != input_event_container_[index].end();++it)
		{
			if(*it == input_event)
			{
				input_event_container_[index].erase(it);
				break;
			}
		}
	}
}

//=============================================================================
// load
//=============================================================================
bool DIVirtual::Load(const s8* filename)
{
	FILE* file = nullptr;
	u32 size = 0;
	u32 key = 0;

	fopen_s(&file,filename,"rb");

	if(file == nullptr)
	{
		return false;
	}

	for(u32 i = 0;i < KEY_MAX;++i)
	{
		fread(&size,sizeof(u32),1,file);
	
		for(u32 j = 0;j < size;++j)
		{
			fread(&key,sizeof(u32),1,file);
			input_event_container_[i].push_back((INPUT_EVENT)key);
		}
	}

	fclose(file);

	return true;
}

//=============================================================================
// save
//=============================================================================
bool DIVirtual::Save(const s8* filename)
{
	FILE* file = nullptr;

	fopen_s(&file,filename,"wb");

	for(u32 i = 0;i < KEY_MAX;++i)
	{
		u32 size = input_event_container_[i].size();
		fwrite(&size,sizeof(u32),1,file);
		for(u32 j = 0;j < size;++j)
		{
			u32 key = input_event_container_[i][j];
			fwrite(&key,sizeof(u32),1,file);
		}
	}

	fclose(file);

	return true;
}

//---------------------------------- EOF --------------------------------------
