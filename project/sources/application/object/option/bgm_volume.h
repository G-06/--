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
	void Adjustvolume(f32 volume);

	void Select(bool is_select);

private:
	static const f32 VOLUME_MAX;
	static const f32 VOLUME_MIN;
	static const D3DXVECTOR2 SIZE;
	Sprite* volume_gage_;
	Sprite* bgm_button_;

	f32 bgm_volume_;
};

#endif	// _OPTION_MENU_H_

//---------------------------------- EOF --------------------------------------
