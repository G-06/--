//*****************************************************************************
//
// bgm volume
//
// Author		: Ryotaro Arai
//				: masato masuda
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
class OptionSpriteSmooth;

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
	void __position(const D3DXVECTOR2 position, const float offset_x);

private:
	static const f32 VOLUME_MAX;
	static const f32 VOLUME_MIN;
	static const D3DXVECTOR2 SIZE;

	OptionSpriteSmooth* volume_gauge_;
	OptionSpriteSmooth* volume_gauge_frame_;
	OptionSpriteSmooth* volume_gauge_back_;

	OptionSpriteSmooth* bgm_string_;
	OptionSpriteSmooth* bgm_string_frame_;

	f32 bgm_volume_;
};

#endif	// _BGM_VOLUME_H_

//---------------------------------- EOF --------------------------------------
