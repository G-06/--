//*****************************************************************************
//
// effect lightning
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _EFFECT_LIGHTNING_H_
#define _EFFECT_LIGHTNING_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "effect.h"
#include "common/animation/animation.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Sprite;

//*****************************************************************************
// class definition
//*****************************************************************************
class EffectLightning : public Effect
{
public:
	// constructor
	EffectLightning(void);

	// destructor
	virtual ~EffectLightning(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

private:
	static const Animation::DATA LIGHTNING_EFFECT[13];
	Sprite* sprite_;
	u32 frame_count_;
	Animation* animation_;
};

#endif	// _EFFECT_CHECK_POINT_H_

//---------------------------------- EOF --------------------------------------
