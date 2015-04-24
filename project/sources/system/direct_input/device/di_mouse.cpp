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

	// デバイスの作成
	hresult = direct_input_->CreateDevice(GUID_SysMouse,&direct_input_device_,NULL);

	// エラー処理
	if(FAILED(hresult))
	{
		return false;
	}

	// データフォーマット設定
	hresult = direct_input_device_->SetDataFormat(&c_dfDIMouse2);

	// エラー処理
	if(FAILED(hresult))
	{
		return false;
	}

	// 協調モードの設定(他のアプリケーションとのデバイスの共有方法)
	hresult = direct_input_device_->SetCooperativeLevel(window_->__hwnd(),(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));

	// エラー処理
	if(FAILED(hresult))
	{
		return false;
	}

	// マウスへのアクセス権を取得
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

	// マウスの情報取得
	if(SUCCEEDED(direct_input_device_->GetDeviceState(sizeof(temp_state),&temp_state)))
	{
		// スクリーン座標取得
		GetCursorPos(&pos);

		// スクリーン座標からクライアント座標に変換
		ScreenToClient(window_->__hwnd(),&pos);

		// 座標を設定
		input_event_buffer_->SetValue(INPUT_EVENT_VALUE_MOUSE_X,pos.x);
		input_event_buffer_->SetValue(INPUT_EVENT_VALUE_MOUSE_Y,pos.y);

		// 差分を設定
		input_event_buffer_->SetValue(INPUT_EVENT_VALUE_MOUSE_MOVE_X,temp_state.lX);
		input_event_buffer_->SetValue(INPUT_EVENT_VALUE_MOUSE_MOVE_Y,temp_state.lY);

		// スクロール量取得
		input_event_buffer_->SetValue(INPUT_EVENT_VALUE_MOUSE_SCROLL,temp_state.lZ);
	}
	else
	{
		// アクセス権を再取得
		direct_input_device_->Acquire();
	}

	for(int i = 0; i < KEY_MAX;++i)
	{
		const bool press_key = (temp_state.rgbButtons[i] & PUSH_BIT) ? true : false;

		// トリガーキーの算出
		const bool trigger_key = (preview_key_[i] ^ press_key) & press_key;

		// リリースキーの算出
		const bool release_key = (preview_key_[i] ^ press_key) & !press_key;

		// プレビューキーの保存
		preview_key_[i] = press_key;

		input_event_buffer_->SetPress(static_cast<INPUT_EVENT>(INPUT_EVENT_LCLICK + i),press_key);
		input_event_buffer_->SetTrigger(static_cast<INPUT_EVENT>(INPUT_EVENT_LCLICK + i),trigger_key);
		input_event_buffer_->SetRelease(static_cast<INPUT_EVENT>(INPUT_EVENT_LCLICK + i),release_key);
	}
}

//---------------------------------- EOF --------------------------------------