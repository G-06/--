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

	void Start(void);

	bool __is_free(void){ return is_free_;}
	void __is_free(bool is_free){ is_free_ = is_free;}

private:
	static const D3DXVECTOR2 DOWN_SIZE;
	bool is_free_;
	Sprite* sprite_;
	f32 alpha_;
};

#endif	// _EFFECT_LOCUS_H_

//---------------------------------- EOF --------------------------------------
