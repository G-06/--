//*****************************************************************************
//
// effect game start
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _EFFECT_GAME_START_H_
#define _EFFECT_GAME_START_H_

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
class EffectGameStart : public AssertEffect
{
public:
	// constructor
	EffectGameStart(TYPE type);

	// destructor
	virtual ~EffectGameStart(void);

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

#endif	// _EFFECT_GAME_STRAT_H_

//---------------------------------- EOF --------------------------------------
