//*****************************************************************************
//
// assert effect gameover
//
// Author		: taichi kitazawa
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _ASSERT_EFFECT_GAMEOVER_H_
#define _ASSERT_EFFECT_GAMEOVER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "assert_effect.h"

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
class AssertEffectGameover : public AssertEffect
{
public:
	// constructor
	AssertEffectGameover(void);

	// destructor
	virtual ~AssertEffectGameover(void);

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
	static const f32 FADE_IN_FRAME;
	static const u32 SRIDE_IN_FRAME;
	static const u32 STOP_FRAME;
	static const u32 SRIDE_OUT_FRAME;
	static const f32 MAX_ALPHA;
	Sprite* sprite_;
	D3DXVECTOR2 position_;
	D3DXVECTOR2 purpose_position_;
	u32 frame_count_;

	Sprite* fade_;
	f32 alpha_;


	bool is_stop_;

};

#endif	// _ASSERT_EFFECT_GAMEOVER_H_

//---------------------------------- EOF --------------------------------------
