//*****************************************************************************
//
// assert effect clear
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _ASSERT_EFFECT_CLEAR_H_
#define _ASSERT_EFFECT_CLEAR_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "assert_effect.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Sprite;

//*****************************************************************************
// class definition
//*****************************************************************************
class AssertEffectClear : public AssertEffect
{
public:
	// constructor
	AssertEffectClear(void);

	// destructor
	virtual ~AssertEffectClear(void);

	// initialize
	virtual bool Initialize(void);

	// uninitialize
	virtual void Uninitialize(void);

	// update
	virtual void Update(void);

	// draw
	virtual void Draw(void);

	// accessor
	bool __is_stop(void) { return is_stop_; }
private:
	static const u32 SRIDE_IN_FRAME;
	static const u32 STOP_FRAME;
	static const u32 SRIDE_OUT_FRAME;
	Sprite* sprite_;
	D3DXVECTOR2 position_;
	D3DXVECTOR2 purpose_position_;
	u32 frame_count_;
	u32 time_;
	bool is_stop_;
};

#endif	// _ASSERT_EFFECT_CLEAR_H_

//---------------------------------- EOF --------------------------------------
