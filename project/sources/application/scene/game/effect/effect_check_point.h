//*****************************************************************************
//
// effect check point
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _EFFECT_CHECK_POINT_H_
#define _EFFECT_CHECK_POINT_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "effect.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Sprite;

//*****************************************************************************
// class definition
//*****************************************************************************
class EffectCheckPoint : public Effect
{
public:
	// constructor
	EffectCheckPoint(void);

	// destructor
	virtual ~EffectCheckPoint(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

private:
	Sprite* sprite_;
	u32 frame_count_;
};

#endif	// _EFFECT_CHECK_POINT_H_

//---------------------------------- EOF --------------------------------------
