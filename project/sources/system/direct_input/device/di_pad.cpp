//*****************************************************************************
//
// direct input pad
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "di_pad.h"
#include "system/system.h"
#include "../input_event_buffer.h"

//=============================================================================
// constructor
//=============================================================================
DIPad::DIPad(LPDIRECTINPUT8 direct_input,Window* window,InputEventBuffer* input_event_buffer)
	:DIDevice(direct_input,window,input_event_buffer)
	,input_type_(INPUT_TYPE_NONE)
{
}

//=============================================================================
// destructor
//=============================================================================
DIPad::~DIPad(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool DIPad::Initialize(void)
{
	if(FAILED(direct_input_->EnumDevices(DI8DEVCLASS_GAMECTRL,DIEnumDevicesCallback,this,DIEDFL_ATTACHEDONLY)))
	{
		ASSERT("ジョイパッドがありません！");
		return false;
	}

	if(input_type_ == INPUT_TYPE_DIRECT_INPUT)
	{
		if(direct_input_device_ != nullptr)
		{
			// データフォーマットを設定
			if(FAILED(direct_input_device_->SetDataFormat(&c_dfDIJoystick2)))
			{
				ASSERT("データフォーマットの設定,ジョイパッドのデータフォーマットを設定できませんでした。");
				return false;
			}

			// 協調モードを設定（フォアグラウンド＆非排他モード）
			if(FAILED(direct_input_device_->SetCooperativeLevel(window_->__hwnd(),(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
			{
				ASSERT("強調モードの設定,ジョイパッドの協調モードを設定できませんでした。");
				return false;
			}

			if(FAILED(direct_input_device_->EnumObjects(EnumObjectsProc,this,DIDFT_AXIS)))
			{
				ASSERT("デバイス上で使用可能な入出力オブジェクトを列挙,ジョイパッドの設定ができませんでした。");
				return false;
			}

			// キーボードへのアクセス権を獲得(入力制御開始)
			direct_input_device_->Acquire();
		}
		else
		{
			return false;
		}
	}
	else if(input_type_ == INPUT_TYPE_NONE)
	{
		return false;
	}

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void DIPad::Uninitialize(void)
{
	DIDevice::Uninitialize();
}

//=============================================================================
// update
//=============================================================================
void DIPad::Update(void)
{
	DIJOYSTATE2 dijoystate2 = {NULL};
	bool press_key[PAD_MAX] = {false};

	if(input_type_ == INPUT_TYPE_DIRECT_INPUT)
	{
		if(FAILED(direct_input_device_->GetDeviceState(sizeof(dijoystate2),&dijoystate2)))
		{
			direct_input_device_->Acquire();
		}

		press_key[PAD_KEY_MAX + 1] = ((dijoystate2.rgdwPOV[0] >= 315 * 100 && dijoystate2.rgdwPOV[0] <= 360 * 100) || (dijoystate2.rgdwPOV[0] >= 0 * 100 && dijoystate2.rgdwPOV[0] <= 45 * 100));
		press_key[PAD_KEY_MAX + 2] = (dijoystate2.rgdwPOV[0] >= 135 * 100 && dijoystate2.rgdwPOV[0] <= 225 * 100);
		press_key[PAD_KEY_MAX + 3] = (dijoystate2.rgdwPOV[0] >= 225 * 100 && dijoystate2.rgdwPOV[0] <= 315 * 100);
		press_key[PAD_KEY_MAX + 4] = (dijoystate2.rgdwPOV[0] >= 45 * 100 && dijoystate2.rgdwPOV[0] <= 135 * 100);

		for(u32 i = (PAD_KEY_MAX + 5);i < PAD_MAX;++i)
		{
			press_key[i] = (dijoystate2.rgbButtons[i - PAD_KEY_MAX - 5] == 128 ? true : false);
		}

		press_key[INPUT_EVENT_PAD_L_LEFT - INPUT_EVENT_PAD_L_LEFT]  = dijoystate2.lX  < -DIRECT_INPUT_DEEP_X;
		press_key[INPUT_EVENT_PAD_L_RIGHT - INPUT_EVENT_PAD_L_LEFT] = dijoystate2.lX  >  DIRECT_INPUT_DEEP_X;
		press_key[INPUT_EVENT_PAD_L_UP - INPUT_EVENT_PAD_L_LEFT]    = dijoystate2.lY  < -DIRECT_INPUT_DEEP_Y;
		press_key[INPUT_EVENT_PAD_L_DOWN - INPUT_EVENT_PAD_L_LEFT]  = dijoystate2.lY  >  DIRECT_INPUT_DEEP_Y;
		press_key[INPUT_EVENT_PAD_R_LEFT - INPUT_EVENT_PAD_L_LEFT]  = dijoystate2.lZ  < -DIRECT_INPUT_DEEP_X;
		press_key[INPUT_EVENT_PAD_R_RIGHT - INPUT_EVENT_PAD_L_LEFT] = dijoystate2.lZ  >  DIRECT_INPUT_DEEP_X;
		press_key[INPUT_EVENT_PAD_R_UP - INPUT_EVENT_PAD_L_LEFT]    = dijoystate2.lRz < -DIRECT_INPUT_DEEP_X;
		press_key[INPUT_EVENT_PAD_R_DOWN - INPUT_EVENT_PAD_L_LEFT]  = dijoystate2.lRz >  DIRECT_INPUT_DEEP_X;

		input_event_buffer_->SetValue(INPUT_EVENT_VALUE_PAD_LSTICK_X,dijoystate2.lX);
		input_event_buffer_->SetValue(INPUT_EVENT_VALUE_PAD_LSTICK_Y,dijoystate2.lY);
		input_event_buffer_->SetValue(INPUT_EVENT_VALUE_PAD_RSTICK_X,dijoystate2.lRx);
		input_event_buffer_->SetValue(INPUT_EVENT_VALUE_PAD_RSTICK_Y,dijoystate2.lRy);
	}
	else if(input_type_ == INPUT_TYPE_X_INPUT)
	{
		XINPUT_STATE xinput_state = {NULL};
		XInputGetState(0,&xinput_state);

		press_key[INPUT_EVENT_PAD_L_LEFT - INPUT_EVENT_PAD_L_LEFT]  = xinput_state.Gamepad.sThumbLX < -X_INPUT_DEEP;
		press_key[INPUT_EVENT_PAD_L_RIGHT - INPUT_EVENT_PAD_L_LEFT] = xinput_state.Gamepad.sThumbLX >  X_INPUT_DEEP;
		press_key[INPUT_EVENT_PAD_L_UP - INPUT_EVENT_PAD_L_LEFT]    = xinput_state.Gamepad.sThumbLY >  X_INPUT_DEEP;
		press_key[INPUT_EVENT_PAD_L_DOWN - INPUT_EVENT_PAD_L_LEFT]  = xinput_state.Gamepad.sThumbLY < -X_INPUT_DEEP;
		press_key[INPUT_EVENT_PAD_R_LEFT - INPUT_EVENT_PAD_L_LEFT]  = xinput_state.Gamepad.sThumbRX < -X_INPUT_DEEP;
		press_key[INPUT_EVENT_PAD_R_RIGHT - INPUT_EVENT_PAD_L_LEFT] = xinput_state.Gamepad.sThumbRX >  X_INPUT_DEEP;
		press_key[INPUT_EVENT_PAD_R_UP - INPUT_EVENT_PAD_L_LEFT]    = xinput_state.Gamepad.sThumbRY >  X_INPUT_DEEP;
		press_key[INPUT_EVENT_PAD_R_DOWN - INPUT_EVENT_PAD_L_LEFT]  = xinput_state.Gamepad.sThumbRY < -X_INPUT_DEEP;

		for(u32 i = (PAD_KEY_MAX + 1);i < PAD_MAX;++i)
		{
			press_key[i] = ((xinput_state.Gamepad.wButtons >> (i - PAD_KEY_MAX - 1)) & 0x0001) ? true : false;
		}

		press_key[18] = xinput_state.Gamepad.bLeftTrigger  > X_INPUT_TRIGGER_DEEP;
		press_key[19] = xinput_state.Gamepad.bRightTrigger > X_INPUT_TRIGGER_DEEP;

		input_event_buffer_->SetValue(INPUT_EVENT_VALUE_PAD_LSTICK_X,xinput_state.Gamepad.sThumbLX);
		input_event_buffer_->SetValue(INPUT_EVENT_VALUE_PAD_LSTICK_Y,xinput_state.Gamepad.sThumbLY);
		input_event_buffer_->SetValue(INPUT_EVENT_VALUE_PAD_RSTICK_X,xinput_state.Gamepad.sThumbRX);
		input_event_buffer_->SetValue(INPUT_EVENT_VALUE_PAD_RSTICK_Y,xinput_state.Gamepad.sThumbLY);

	}

	for(u32 i = 0; i < PAD_MAX;++i)
	{
		// トリガーキーの算出
		bool trigger_key = (press_key[i] ^ preview_key_[i]) & press_key[i];

		// リリースキーの算出
		bool release_key = (press_key[i] ^ preview_key_[i]) & !press_key[i];

		// プレビューキーの保存
		preview_key_[i] = press_key[i];

		input_event_buffer_->SetPress(static_cast<INPUT_EVENT>(i + INPUT_EVENT_PAD_L_LEFT),press_key[i]);
		input_event_buffer_->SetTrigger(static_cast<INPUT_EVENT>(i + INPUT_EVENT_PAD_L_LEFT),trigger_key);
		input_event_buffer_->SetRelease(static_cast<INPUT_EVENT>(i + INPUT_EVENT_PAD_L_LEFT),release_key);
	}

	static const s8 input_type_name[][256] =
	{
		"DIRECT_INPUT",
		"X_INPUT",
	};

	static const s8 button_name[][256] =
	{
		"L_LEFT",
		"L_RIGHT",
		"L_UP",
		"L_DOWN",
		"R_LEFT",
		"R_RIGHT",
		"R_UP",
		"R_DOWN",
	};

	DEBUG_TOOL.__debug_display()->Print("Input Type : %s\n",input_type_name[input_type_]);

	for(u32 i = 0; i <= PAD_KEY_MAX;++i)
	{
		DEBUG_TOOL.__debug_display()->Print("%s : %d\n",button_name[i],input_event_buffer_->CheckPress(static_cast<INPUT_EVENT>(i + INPUT_EVENT_PAD_L_LEFT)));
	}

	DEBUG_TOOL.__debug_display()->Print("Button : ");

	for(u32 i = 0; i < PAD_BUTTON_MAX;++i)
	{
		if(input_event_buffer_->CheckPress(static_cast<INPUT_EVENT>(i + INPUT_EVENT_PAD_0)))
		{
			DEBUG_TOOL.__debug_display()->Print("%d,",i);
		}
	}
}

//=============================================================================
// ジョイスティック問い合わせ用コールバック関数
//=============================================================================
BOOL CALLBACK DIPad::DIEnumDevicesCallback(const DIDEVICEINSTANCE* lpddi,void* ref)
{
	DIDEVCAPS	diDevCaps;			// デバイス情報
	HRESULT		hRes;
	DIPad* di_pad = (DIPad*)ref;

	if(di_pad->IsXInputDevice(&lpddi->guidProduct))
	{
		di_pad->input_type_ = INPUT_TYPE_X_INPUT;
		return DIENUM_CONTINUE;
	}

	if(FAILED(di_pad->direct_input_->CreateDevice(lpddi->guidInstance,&(di_pad->direct_input_device_),NULL)))
	{
		return DIENUM_CONTINUE;		// 列挙を続ける
	}

	// ジョイスティックの能力を調べる
	diDevCaps.dwSize = sizeof(DIDEVCAPS);

	if(FAILED(di_pad->direct_input_device_->GetCapabilities(&diDevCaps)))
	{
		SafeRelease(di_pad->direct_input_device_);
		return DIENUM_CONTINUE;		// 列挙を続ける
	}

	di_pad->input_type_ = INPUT_TYPE_DIRECT_INPUT;

	return DIENUM_STOP;		// このデバイスを使うので列挙を終了する
}

//=============================================================================
// ジョイスティック問い合わせ用コールバック関数
//=============================================================================
BOOL CALLBACK DIPad::EnumObjectsProc(const LPCDIDEVICEOBJECTINSTANCE lpddoi,void* ref)
{
	DIPad* di_pad = (DIPad*)ref;

	// 軸の値の範囲を設定（-1000～1000）
	DIPROPRANGE diprg;
	ZeroMemory(&diprg, sizeof(diprg));
	diprg.diph.dwSize	= sizeof(diprg); 
	diprg.diph.dwHeaderSize	= sizeof(diprg.diph); 
	diprg.diph.dwObj	= lpddoi->dwType;
	diprg.diph.dwHow	= DIPH_BYID;
	diprg.lMin	= -1000;
	diprg.lMax	= +1000;

	if(FAILED(di_pad->direct_input_device_->SetProperty(DIPROP_RANGE,&diprg.diph)))
	{
		return DIENUM_STOP;
	}

	return DIENUM_CONTINUE;
}

//-----------------------------------------------------------------------------
// Enum each PNP device using WMI and check each device ID to see if it contains
// "IG_" (ex. "VID_045E&PID_028E&IG_00").  If it does, then it's an XInput device
// Unfortunately this information can not be found by just using DirectInput
//-----------------------------------------------------------------------------
bool DIPad::IsXInputDevice(const GUID* pGuidProductFromDirectInput)
{
	IWbemLocator*           pIWbemLocator = NULL;
	IEnumWbemClassObject*   pEnumDevices = NULL;
	IWbemClassObject*       pDevices[20] = {0};
	IWbemServices*          pIWbemServices = NULL;
	BSTR                    bstrNamespace = NULL;
	BSTR                    bstrDeviceID = NULL;
	BSTR                    bstrClassName = NULL;
	DWORD                   uReturned = 0;
	bool                    bIsXinputDevice = false;
	UINT                    iDevice = 0;
	VARIANT                 var;
	HRESULT                 hr;
	// CoInit if needed
	hr = CoInitialize(NULL);
	bool bCleanupCOM = SUCCEEDED(hr);
	// Create WMI
	hr = CoCreateInstance(__uuidof(WbemLocator),
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(IWbemLocator),
		(LPVOID*)&pIWbemLocator);
	if(FAILED(hr) || pIWbemLocator == NULL)
		goto LCleanup;
	bstrNamespace = SysAllocString(L"\\\\.\\root\\cimv2");
	if(bstrNamespace == NULL) goto LCleanup;
	bstrClassName = SysAllocString(L"Win32_PNPEntity");
	if(bstrClassName == NULL) goto LCleanup;
	bstrDeviceID = SysAllocString(L"DeviceID");
	if(bstrDeviceID == NULL)  goto LCleanup;
	// Connect to WMI
	hr = pIWbemLocator->ConnectServer(bstrNamespace,NULL,NULL,0L,
		0L,NULL,NULL,&pIWbemServices);
	if(FAILED(hr) || pIWbemServices == NULL)
		goto LCleanup;
	// Switch security level to IMPERSONATE.
	CoSetProxyBlanket(pIWbemServices,RPC_C_AUTHN_WINNT,RPC_C_AUTHZ_NONE,NULL,
		RPC_C_AUTHN_LEVEL_CALL,RPC_C_IMP_LEVEL_IMPERSONATE,NULL,EOAC_NONE);
	hr = pIWbemServices->CreateInstanceEnum(bstrClassName,0,NULL,&pEnumDevices);
	if(FAILED(hr) || pEnumDevices == NULL)
		goto LCleanup;
	// Loop over all devices
	for(;;)
	{
		// Get 20 at a time
		hr = pEnumDevices->Next(10000,20,pDevices,&uReturned);
		if(FAILED(hr))
			goto LCleanup;
		if(uReturned == 0)
			break;
		for(iDevice = 0; iDevice<uReturned; iDevice++)
		{
			// For each device, get its device ID
			hr = pDevices[iDevice]->Get(bstrDeviceID,0L,&var,NULL,NULL);
			if(SUCCEEDED(hr) && var.vt == VT_BSTR && var.bstrVal != NULL)
			{
				// Check if the device ID contains "IG_".  If it does, then it's an XInput device
				// This information can not be found from DirectInput
				if( wcsstr( var.bstrVal, L"IG_" ) )
				{
					// If it does, then get the VID/PID from var.bstrVal
					DWORD dwPid = 0, dwVid = 0;
					WCHAR* strVid = wcsstr( var.bstrVal, L"VID_" );
					if( strVid && swscanf( strVid, L"VID_%4X", &dwVid ) != 1 )
						dwVid = 0;
					WCHAR* strPid = wcsstr( var.bstrVal, L"PID_" );
					if( strPid && swscanf( strPid, L"PID_%4X", &dwPid ) != 1 )
						dwPid = 0;
					// Compare the VID/PID to the DInput device
					DWORD dwVidPid = MAKELONG( dwVid, dwPid );
					if( dwVidPid == pGuidProductFromDirectInput->Data1 )
					{
						bIsXinputDevice = true;
						goto LCleanup;
					}
				}
			}
			SafeRelease(pDevices[iDevice]);
		}
	}
LCleanup:
	if(bstrNamespace)
		SysFreeString(bstrNamespace);
	if(bstrDeviceID)
		SysFreeString(bstrDeviceID);
	if(bstrClassName)
		SysFreeString(bstrClassName);
	for(iDevice = 0; iDevice<20; iDevice++)
		SafeRelease(pDevices[iDevice]);
	SafeRelease(pEnumDevices);
	SafeRelease(pIWbemLocator);
	SafeRelease(pIWbemServices);
	if(bCleanupCOM)
		CoUninitialize();
	return bIsXinputDevice;
}

//---------------------------------- EOF --------------------------------------
