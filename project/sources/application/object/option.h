//*****************************************************************************
//
// option
//
// Author		: Ryotaro Arai
//
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _OPTION_H_
#define _OPTION_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class OptionBg;
class OptionMenu;

//*****************************************************************************
// class definition
//*****************************************************************************
class Option : public Basic
{
public:
	enum OPTION_SCENE
	{
		OPTION_MIN = -1,
		OPTION_MENU = 0,
		OPTION_CONFIG_1,
		OPTION_CONFIG_2,
		OPTION_VOLUME,
		OPTION_MAX
	};
	enum MENU_NUM
	{
		MENU_MIN = -1,
		MENU_CONFIG = 0,
		MENU_VOLUME,
		MENU_MAX
	};

	// constructor
	Option(void);

	// destructor
	virtual ~Option(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	void Update(void);

	void Draw(void);

	private:
	OptionBg* option_bg_;
	OptionMenu* option_menu_;
	OPTION_SCENE option_scene_;
	u32 cursor_;
};

#endif	// _OPTION_H_

//---------------------------------- EOF --------------------------------------
