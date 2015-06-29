//*****************************************************************************
//
// effect locus
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _EFFECT_LOCUS_H_
#define _EFFECT_LOCUS_H_

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
class EffectLocus : public Effect
{
public:
	// constructor
	EffectLocus(void);

	// destructor
	virtual ~EffectLocus(void);

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
	f32 alpha_;
};

#endif	// _EFFECT_LOCUS_H_

//---------------------------------- EOF --------------------------------------
