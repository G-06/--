//*****************************************************************************
//
// gimmick disappear ground
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _GIMMICK_DISAPPEAR_GROUND_H_
#define _GIMMICK_DISAPPEAR_GROUND_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "gimmick.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class ObjectDisappearGround;

//*****************************************************************************
// class definition
//*****************************************************************************
class GimmickDisappearGround : public Gimmick
{
public:
	struct DATA
	{
		bool _is_hit;
	};

	// constructor
	GimmickDisappearGround(void);

	// destructor
	virtual ~GimmickDisappearGround(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// get pointer
	void* GetPointer(void);

	// accessor
	void __appear_frame(u32 appear_frame) { appear_frame_ = appear_frame; }
	void __disappear_frame(u32 disappear_frame) { disappear_frame_ = disappear_frame; }
	bool __is_show(void) { return is_show_; }

private:
	ObjectDisappearGround* object_disappear_ground_;
	u32 appear_frame_;
	u32 disappear_frame_;
	bool is_show_;
	u32 frame_count_;
	DATA data_;
};

#endif	// _GIMMICK_DISAPPEAR_GROUND_H_

//---------------------------------- EOF --------------------------------------
