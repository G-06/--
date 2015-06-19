//*****************************************************************************
//
// key config cancel
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _KEY_CONFIG_CANCEL_H_
#define _KEY_CONFIG_CANCEL_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"
#include "system/system.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Sprite;

//*****************************************************************************
// class definition
//*****************************************************************************
class KeyConfigCancel : public Basic
{
public:
	// constructor
	KeyConfigCancel(void);

	// destructor
	virtual ~KeyConfigCancel(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// ‘I‘ð
	void Select(bool is_select);

	void __set_button_number_texture(INPUT_EVENT button);

private:
	Sprite* cancel_button_;
	Sprite* set_button_number_;

	u32 current_key_event_;
};

#endif	// _OPTION_MENU_H_

//---------------------------------- EOF --------------------------------------
