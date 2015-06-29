//*****************************************************************************
//
// effect dead
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _EFFECT_DEAD_H_
#define _EFFECT_DEAD_H_

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
class EffectDead : public Effect
{
public:
	// constructor
	EffectDead(void);

	// destructor
	virtual ~EffectDead(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

private:
	static const s32 DEAD_EFFECT_PATTERN = 8;
	static const Animation::DATA DEAD_EFFECT[DEAD_EFFECT_PATTERN];
	Sprite* sprite_;
	u32 frame_count_;
	Animation* animation_;
};

#endif	// _EFFECT_DEAD_H_

//---------------------------------- EOF --------------------------------------
