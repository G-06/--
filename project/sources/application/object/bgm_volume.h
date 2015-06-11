//*****************************************************************************
//
// bgm volume
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _BGM_VOLUME_H_
#define _BGM_VOLUME_H_

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
class BgmVolume : public Basic
{
public:
	const static u32 MAX_VOLUME = (9);
	const static u32 MIN_VOLUME = (0);

	// constructor
	BgmVolume(void);

	// destructor
	virtual ~BgmVolume(void);

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

	void Select(bool is_select);

private:
	Sprite* volume_gage_;
	Sprite* bgm_button_;

	s32 bgm_volume_;
};

#endif	// _OPTION_MENU_H_

//---------------------------------- EOF --------------------------------------
