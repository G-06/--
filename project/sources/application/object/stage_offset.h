//*****************************************************************************
//
// stage offset
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _STAGE_OFFSET_H_
#define _STAGE_OFFSET_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"

//*****************************************************************************
// class definition
//*****************************************************************************
class StageOffset : public Basic
{
public:
	// constructor
	StageOffset(void);

	// destructor
	virtual ~StageOffset(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// accessor
	const D3DXVECTOR2& __position(void)const { return position_; }
	void __stage_size(const D3DXVECTOR2& stage_size) { stage_size_ = stage_size; }
	void __reference_position(const D3DXVECTOR2& reference_position) { reference_position_ = reference_position; }
	void __old_reference_position(const D3DXVECTOR2& old_reference_position) { old_reference_position_ = old_reference_position; }
	void __screen_size(const D3DXVECTOR2& screen_size) { screen_size_ = screen_size; }

	static const f32 OFFSET_MOVE;

private:
	D3DXVECTOR2 position_;
	D3DXVECTOR2 stage_size_;
	D3DXVECTOR2 reference_position_;
	D3DXVECTOR2 old_reference_position_;
	D3DXVECTOR2 screen_size_;
	D3DXVECTOR2 offset_percent_;
	D3DXVECTOR2 offset_move_;
};

#endif	// _STAGE_OFFSET_H_

//---------------------------------- EOF --------------------------------------
