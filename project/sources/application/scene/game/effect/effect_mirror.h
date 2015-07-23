//*****************************************************************************
//
// effect mirror
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _EFFECT_MIRROR_H_
#define _EFFECT_MIRROR_H_

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
class EffectMirror : public Effect
{
public:
	// constructor
	EffectMirror(void);

	// destructor
	virtual ~EffectMirror(void);

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
	static const s32 MIRROR_EFFECT_PATTERN = 14;
	static const s32 MIRROR_FRAME = 27;
	static const Animation::DATA MIRROR_EFFECT[MIRROR_EFFECT_PATTERN];
	Sprite* sprite_;
	u32 frame_count_;
	bool is_free_;
	Animation* animation_;
};

#endif	// _EFFECT_MIRROR_H_

//---------------------------------- EOF --------------------------------------
