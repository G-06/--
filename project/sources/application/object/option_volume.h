//*****************************************************************************
//
// option volume
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _OPTION_VOLUME_H_
#define _OPTION_VOLUME_H_

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
class OptionVolume : public Basic
{
public:
	const static u32 MAX_VOLUME = (9);
	const static u32 MIN_VOLUME = (0);

	enum OPTION_TYPE
	{
		SELECT_BUTTON = 0,
		CANCEL_BUTTON,
		LIGHT_BUTTON,
		JUMP_BUTTON,
		BUTTON_MAX
	};
	// constructor
	OptionVolume(void);

	// destructor
	virtual ~OptionVolume(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// Т▓Ро
	void Adjustvolume(u32 volume);

private:
	Sprite* volume_gage_;
};

#endif	// _OPTION_MENU_H_

//---------------------------------- EOF --------------------------------------
