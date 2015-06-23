//*****************************************************************************
//
// se volume
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _SE_VOLUME_H_
#define _SE_VOLUME_H_

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
class SeVolume : public Basic
{
public:
	// constructor
	SeVolume(void);

	// destructor
	virtual ~SeVolume(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// Т▓Ро
	void Adjustvolume(f32 volume);

	void Select(bool is_select);

private:
	Sprite* volume_gage_;
	Sprite* se_button_;

	f32 se_volume_;
};

#endif	// _OPTION_MENU_H_

//---------------------------------- EOF --------------------------------------
