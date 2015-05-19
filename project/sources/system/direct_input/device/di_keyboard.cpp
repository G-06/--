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

	// デバイスオブジェクトを作成
	hresult = direct_input_->CreateDevice(GUID_SysKeyboard,&direct_input_device_,NULL);

	if(FAILED(hresult))
	{
		ASSERT("デバイスオブジェクトの作成に失敗しました。");
		return false;
	}

	// データフォーマットを設定
	hresult = direct_input_device_->SetDataFormat(&c_dfDIKeyboard);

	if(FAILED(hresult))
	{
		ASSERT("データフォーマットの設定に失敗しました。");
		return false;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hresult = direct_input_device_->SetCooperativeLevel(window_->__hwnd(),(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));

	if(FAILED(hresult))
	{
		ASSERT("協調モードの設定に失敗しました。");
		return false;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
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
		// プレスキーの算出
		press_key = (key_state[i] & 0x80) ? true : false;

		// トリガーキーの算出
		trigger_key = (press_key ^ preview_key_[i]) & press_key;

		// リリースキーの算出
		release_key = (press_key ^ preview_key_[i]) & !press_key;

		// プレビューキーの保存
		preview_key_[i] = press_key;

		input_event_buffer_->SetPress(static_cast<INPUT_EVENT>(i),press_key);
		input_event_buffer_->SetTrigger(static_cast<INPUT_EVENT>(i),trigger_key);
		input_event_buffer_->SetRelease(static_cast<INPUT_EVENT>(i),release_key);
	}
}

//---------------------------------- EOF --------------------------------------
