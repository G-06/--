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
class SelectRecord;
class ObjectNewRecord;

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

	// set time
	void SetTime(u32 time);

	// accessor
	bool __is_stop(void) { return is_stop_; }
	void __time(u32 time) { time_ = time; }
	void __set_newrecord_flag(bool flag){new_record_flag_ = flag;};

private:
	static const u32 SRIDE_IN_FRAME;
	static const u32 STOP_FRAME;
	static const u32 SRIDE_OUT_FRAME;
	static const u32 RECORD_SRIDE_IN_FRAME;

	static const u32 NEW_RECORD_SRIDE_IN_FRAME;
	static const u32 NEW_RECORD_STOP_FRAME;

	static const D3DXVECTOR2 CLEAR_START_POSITION;
	static const D3DXVECTOR2 CLEAR_STOP_POSITION;
	static const D3DXVECTOR2 CLEAR_END_POSITION;
	static const D3DXVECTOR2 RECORD_START_POSITION;
	static const D3DXVECTOR2 RECORD_END_POSITION;
	static const D3DXVECTOR2 NEW_RECORD_START_POSITION;
	static const D3DXVECTOR2 NEW_RECORD_END_POSITION;

	Sprite* sprite_;
	SelectRecord* record_;
	ObjectNewRecord* new_record_;

	D3DXVECTOR2 position_;
	D3DXVECTOR2 purpose_position_;
	D3DXVECTOR2 record_position_;
	D3DXVECTOR2 new_record_position_;
	f32 record_alpha_;

	u32 frame_count_;
	u32 time_;
	bool is_stop_;
	bool new_record_flag_;
	bool is_first_;
};

#endif	// _ASSERT_EFFECT_CLEAR_H_

//---------------------------------- EOF --------------------------------------
