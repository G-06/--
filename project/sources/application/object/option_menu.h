//*****************************************************************************
//
// option menu
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _OPTION_MENU_H_
#define _OPTION_MENU_H_

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
class OptionMenu : public Basic
{
public:
	static const D3DXVECTOR2 DEFAULT_MENU_SIZE;
	static const D3DXVECTOR2 EXPAND_MENU_SIZE;
	enum OPTION_TYPE
	{
		OPTION_TYPE_CONFIG = 0,
		OPTION_TYPE_VOLUME,
		OPTION_TYPE_MAX
	};
	// constructor
	OptionMenu(void);

	// destructor
	virtual ~OptionMenu(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// ‘I‘ð
	void Select(u32 menu);

private:
	Sprite* menu_config_;
	Sprite* menu_volume_;
};

#endif	// _OPTION_MENU_H_

//---------------------------------- EOF --------------------------------------
