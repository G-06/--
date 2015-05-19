//*****************************************************************************
//
// direct input keyboard
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "di_keyboard.h"

#include "system/system.h"
#include "../input_event_buffer.h"

//=============================================================================
// constructor
//=============================================================================
DIKeyboard::DIKeyboard(LPDIRECTINPUT8 in_direct_input,Window* in_window,InputEventBuffer* in_input_event_buffer) :
DIDevice(in_direct_input,in_window,in_input_event_buffer)
{
}

//=============================================================================
// destructor
//=============================================================================
DIKeyboard::~DIKeyboard(void)
{
}

//=============================================================================
// initializer
//=============================================================================
bool DIKeyboard::Initialize(void)
{
	HRESULT hresult = E_FAIL;

	// �f�o�C�X�I�u�W�F�N�g���쐬
	hresult = direct_input_->CreateDevice(GUID_SysKeyboard,&direct_input_device_,NULL);

	if(FAILED(hresult))
	{
		ASSERT("�f�o�C�X�I�u�W�F�N�g�̍쐬�Ɏ��s���܂����B");
		return false;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	hresult = direct_input_device_->SetDataFormat(&c_dfDIKeyboard);

	if(FAILED(hresult))
	{
		ASSERT("�f�[�^�t�H�[�}�b�g�̐ݒ�Ɏ��s���܂����B");
		return false;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hresult = direct_input_device_->SetCooperativeLevel(window_->__hwnd(),(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));

	if(FAILED(hresult))
	{
		ASSERT("�������[�h�̐ݒ�Ɏ��s���܂����B");
		return false;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	direct_input_device_->Acquire();

	// initialize key data
	ZeroMemory(preview_key_,KEY_MAX);

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void DIKeyboard::Uninitialize(void)
{
	DIDevice::Uninitialize();
}

//=============================================================================
// update
//=============================================================================
void DIKeyboard::Update(void)
{
	u8 key_state[KEY_MAX];
	bool press_key;
	bool trigger_key;
	bool release_key;

	if(FAILED(direct_input_device_->GetDeviceState(sizeof(key_state),key_state)))
	{
		ZeroMemory(key_state,sizeof(key_state));
		direct_input_device_->Acquire();
	}

	for(int i = 0;i < KEY_MAX;++i)
	{
		// �v���X�L�[�̎Z�o
		press_key = (key_state[i] & 0x80) ? true : false;

		// �g���K�[�L�[�̎Z�o
		trigger_key = (press_key ^ preview_key_[i]) & press_key;

		// �����[�X�L�[�̎Z�o
		release_key = (press_key ^ preview_key_[i]) & !press_key;

		// �v���r���[�L�[�̕ۑ�
		preview_key_[i] = press_key;

		input_event_buffer_->SetPress(static_cast<INPUT_EVENT>(i),press_key);
		input_event_buffer_->SetTrigger(static_cast<INPUT_EVENT>(i),trigger_key);
		input_event_buffer_->SetRelease(static_cast<INPUT_EVENT>(i),release_key);
	}
}

//---------------------------------- EOF --------------------------------------
