//*****************************************************************************
//
// object disappear ground
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _OBJECT_DISAPPEAR_GROUND_H_
#define _OBJECT_DISAPPEAR_GROUND_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Sprite;

//*****************************************************************************
// class definition
//*****************************************************************************
class ObjectDisappearGround : public Basic
{
public:
	// constructor
	ObjectDisappearGround(void);

	// destructor
	virtual ~ObjectDisappearGround(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// show
	void Show(bool is_show);

	// accessor
	void __position(const D3DXVECTOR2& position) { position_ = position; }
	const D3DXVECTOR2& __size(void) { return size_; }
	void __show_frame(u32 show_frame) { show_frame_ = show_frame; }
	bool __is_appear(void) { return is_appear_; }

private:
	static const D3DXVECTOR2 SIZE;
	static const u32 DIVISION_WIDTH;
	static const u32 DIVISION_HEIGHT;

	Sprite* object_disappear_ground_;
	D3DXVECTOR2 position_;
	D3DXVECTOR2 size_;
	bool is_show_;
	u32 show_frame_;
	u32 frame_count_;
	f32 alpha_;
	bool is_appear_;
};

#endif	// _OBJECT_DISAPPEAR_GROUND_H_

//---------------------------------- EOF --------------------------------------
