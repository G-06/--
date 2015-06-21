//*****************************************************************************
//
// effect game end
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _EFFECT_GAME_END_H_
#define _EFFECT_GAME_END_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "scene/game/assert_effect/assert_effect.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************

//*****************************************************************************
// class definition
//*****************************************************************************
class EffectGameEnd : public AssertEffect
{
public:
	// constructor
	EffectGameEnd(TYPE type);

	// destructor
	virtual ~EffectGameEnd(void);

	// initialize
	virtual bool Initialize(void);

	// uninitialize
	virtual void Uninitialize(void);

	// update
	virtual void Update(void);

	// draw
	virtual void Draw(void);

protected:

};

#endif	// _EFFECT_GAME_END_H_

//---------------------------------- EOF --------------------------------------
