//*****************************************************************************
//
// se volume
//
// Author		: Ryotaro Arai
//				: masato masuda
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
class OptionSpriteSmooth;

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

	OptionSpriteSmooth* volume_gauge_;
	OptionSpriteSmooth* se_string_;
	OptionSpriteSmooth* se_string_frame_;

	f32 se_volume_;
};

#endif	// _SE_VOLUME_H_

//---------------------------------- EOF --------------------------------------
