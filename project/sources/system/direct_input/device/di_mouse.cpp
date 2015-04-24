//*****************************************************************************
//
// direct input mouse
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "di_mouse.h"
#include "system/system.h"
#include "../input_event_buffer.h"

//=============================================================================
// constructor
//=============================================================================
DIMouse::DIMouse(LPDIRECTINPUT8 direct_input,Window* window,InputEventBuffer* input_event_buffer) :
DIDevice(direct_input,window,input_event_buffer)
{
}

//=============================================================================
// destructor
//=============================================================================
DIMouse::~DIMouse(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool DIMouse::Initialize(void)
{
	HRESULT hresult = E_FAIL;

	// initialize direct input device
	if(!DIDevice::Initialize())
	{
		return false;
	}

	// �f�o�C�X�̍쐬
	hresult = direct_input_->CreateDevice(GUID_SysMouse,&direct_input_device_,NULL);

	// �G���[����
	if(FAILED(hresult))
	{
		return false;
	}

	// �f�[�^�t�H�[�}�b�g�ݒ�
	hresult = direct_input_device_->SetDataFormat(&c_dfDIMouse2);

	// �G���[����
	if(FAILED(hresult))
	{
		return false;
	}

	// �������[�h�̐ݒ�(���̃A�v���P�[�V�����Ƃ̃f�o�C�X�̋��L���@)
	hresult = direct_input_device_->SetCooperativeLevel(window_->__hwnd(),(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));

	// �G���[����
	if(FAILED(hresult))
	{
		return false;
	}

	// �}�E�X�ւ̃A�N�Z�X�����擾
	direct_input_device_->Acquire();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void DIMouse::Uninitialize(void)
{
	if(direct_input_device_ != nullptr)
	{
		direct_input_device_->Unacquire();
		direct_input_device_->Release();
		direct_input_device_ = nullptr;
	}

	DIDevice::Uninitialize();
}

//=============================================================================
// update
//=============================================================================
void DIMouse::Update(void)
{
	POINT pos;
	DIMOUSESTATE2 temp_state = {NULL};

	// �}�E�X�̏��擾
	if(SUCCEEDED(direct_input_device_->GetDeviceState(sizeof(temp_state),&temp_state)))
	{
		// �X�N���[�����W�擾
		GetCursorPos(&pos);

		// �X�N���[�����W����N���C�A���g���W�ɕϊ�
		ScreenToClient(window_->__hwnd(),&pos);

		// ���W��ݒ�
		input_event_buffer_->SetValue(INPUT_EVENT_VALUE_MOUSE_X,pos.x);
		input_event_buffer_->SetValue(INPUT_EVENT_VALUE_MOUSE_Y,pos.y);

		// ������ݒ�
		input_event_buffer_->SetValue(INPUT_EVENT_VALUE_MOUSE_MOVE_X,temp_state.lX);
		input_event_buffer_->SetValue(INPUT_EVENT_VALUE_MOUSE_MOVE_Y,temp_state.lY);

		// �X�N���[���ʎ擾
		input_event_buffer_->SetValue(INPUT_EVENT_VALUE_MOUSE_SCROLL,temp_state.lZ);
	}
	else
	{
		// �A�N�Z�X�����Ď擾
		direct_input_device_->Acquire();
	}

	for(int i = 0; i < KEY_MAX;++i)
	{
		const bool press_key = (temp_state.rgbButtons[i] & PUSH_BIT) ? true : false;

		// �g���K�[�L�[�̎Z�o
		const bool trigger_key = (preview_key_[i] ^ press_key) & press_key;

		// �����[�X�L�[�̎Z�o
		const bool release_key = (preview_key_[i] ^ press_key) & !press_key;

		// �v���r���[�L�[�̕ۑ�
		preview_key_[i] = press_key;

		input_event_buffer_->SetPress(static_cast<INPUT_EVENT>(INPUT_EVENT_LCLICK + i),press_key);
		input_event_buffer_->SetTrigger(static_cast<INPUT_EVENT>(INPUT_EVENT_LCLICK + i),trigger_key);
		input_event_buffer_->SetRelease(static_cast<INPUT_EVENT>(INPUT_EVENT_LCLICK + i),release_key);
	}
}

//---------------------------------- EOF --------------------------------------