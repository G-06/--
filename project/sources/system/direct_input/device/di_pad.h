//*****************************************************************************
//
// direct input pad
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include gaurd
//*****************************************************************************
#pragma once
#ifndef _DI_PAD_H_
#define _DI_PAD_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "di_device.h"
#include "../input_alias.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class DIPad : public DIDevice
{
public:
	// constructor
	DIPad(LPDIRECTINPUT8 direct_input,Window* window,InputEventBuffer* input_event_buffer);

	// destructor
	virtual ~DIPad(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

private:
	enum INPUT_TYPE
	{
		INPUT_TYPE_NONE = -1,
		INPUT_TYPE_DIRECT_INPUT = 0,
		INPUT_TYPE_X_INPUT,
		INPUT_TYPE_MAX,
	};

	// アナログスティックの受け取り範囲
	static const s32 X_INPUT_DEEP = 5000;
	static const s8 X_INPUT_TRIGGER_DEEP = 10;
	static const s32 DIRECT_INPUT_DEEP_X = 15;
	static const s32 DIRECT_INPUT_DEEP_Y = 290;
	static const u32 PAD_MAX = INPUT_EVENT_PAD_25 - INPUT_EVENT_PAD_L_LEFT;
	static const u32 PAD_KEY_MAX = INPUT_EVENT_PAD_R_DOWN - INPUT_EVENT_PAD_L_LEFT;
	static const u32 PAD_BUTTON_MAX = INPUT_EVENT_PAD_25 - INPUT_EVENT_PAD_0;

	bool preview_key_[PAD_MAX];
	INPUT_TYPE input_type_;

	// XInput
	bool IsXInputDevice(const GUID* pGuidProductFromDirectInput);

	// ジョイスティック問い合わせ用コールバック関数
	static BOOL CALLBACK DIEnumDevicesCallback(const DIDEVICEINSTANCE* lpddi,void* ref);
	static BOOL CALLBACK EnumObjectsProc(const LPCDIDEVICEOBJECTINSTANCE lpddoi,void* ref);
};

#endif // _DI_PAD_H_

//---------------------------------- EOF --------------------------------------
