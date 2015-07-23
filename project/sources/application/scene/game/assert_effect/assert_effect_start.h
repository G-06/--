//*****************************************************************************
//
// assert effect start
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _ASSERT_EFFECT_START_H_
#define _ASSERT_EFFECT_START_H_

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
class AssertEffectStart : public AssertEffect
{
public:
	// constructor
	AssertEffectStart(void);

	// destructor
	virtual ~AssertEffectStart(void);

	// initialize
	virtual bool Initialize(void);

	// uninitialize
	virtual void Uninitialize(void);

	// update
	virtual void Update(void);

	// draw
	virtual void Draw(void);

	// accessor

private:
	static const u32 SRIDE_IN_FRAME;
	static const u32 STOP_FRAME;
	static const u32 SRIDE_OUT_FRAME;
	Sprite* sprite_;
	D3DXVECTOR2 position_;
	D3DXVECTOR2 purpose_position_;
	D3DXVECTOR2 position_back_;
	u32 frame_count_;

	Sprite* sprite_back_;

	bool back_move_;
};

#endif	// _ASSERT_EFFECT_START_H_

//---------------------------------- EOF --------------------------------------
