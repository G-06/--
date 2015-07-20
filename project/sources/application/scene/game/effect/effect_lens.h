//*****************************************************************************
//
// effect lens
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _EFFECT_LENS_H_
#define _EFFECT_LENS_H_

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
class EffectLens : public Effect
{
public:
	// constructor
	EffectLens(void);

	// destructor
	virtual ~EffectLens(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	void Start(void);

	bool __is_free(void){ return is_free_;}
	void __is_free(bool is_free){ is_free_ = is_free;}

private:
	static const s32 LENS_EFFECT_PATTERN = 6;
	static const s32 LENS_FRAME = 17;
	static const Animation::DATA LENS_EFFECT[LENS_EFFECT_PATTERN];
	Sprite* sprite_;
	u32 frame_count_;
	bool is_free_;
	Animation* animation_;
};

#endif	// _EFFECT_LENS_H_

//---------------------------------- EOF --------------------------------------
