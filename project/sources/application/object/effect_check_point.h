//*****************************************************************************
//
// effect
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
#include "scene/game/effect/effect.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************

//*****************************************************************************
// class definition
//*****************************************************************************
class EffectCheckPoint : public Effect
{
public:
	// constructor
	EffectCheckPoint(TYPE type);

	// destructor
	virtual ~EffectCheckPoint(void);

	// initialize
	virtual bool Initialize(void);

	// uninitialize
	virtual void Uninitialize(void);

	// update
	virtual void Update(void);

	// draw
	virtual void Draw(void);

	// accessor


protected:

};

#endif	// _EFFECT_CHECK_POINT_H_

//---------------------------------- EOF --------------------------------------
