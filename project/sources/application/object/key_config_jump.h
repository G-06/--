//*****************************************************************************
//
// key config jump
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _KEY_CONFIG_JUMP_H_
#define _KEY_CONFIG_JUMP_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Sprite;

//*****************************************************************************
// class definition
//*****************************************************************************
class KeyConfigJump : public Basic
{
public:
	// constructor
	KeyConfigJump(void);

	// destructor
	virtual ~KeyConfigJump(void);

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

private:
	Sprite* jump_button_;

	u32 current_key_event_;
};

#endif	// _OPTION_MENU_H_

//---------------------------------- EOF --------------------------------------
