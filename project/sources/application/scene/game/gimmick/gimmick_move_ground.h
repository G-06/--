//*****************************************************************************
//
// gimmick move ground
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _GIMMICK_MOVE_GROUND_H_
#define _GIMMICK_MOVE_GROUND_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "gimmick.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class ObjectMoveGround;

//*****************************************************************************
// class definition
//*****************************************************************************
class GimmickMoveGround : public Gimmick
{
public:
	struct DATA
	{
		D3DXVECTOR2 _move;
	};

	// constructor
	GimmickMoveGround(void);

	// destructor
	virtual ~GimmickMoveGround(void);

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
	void __start_position(const D3DXVECTOR2& start_position) { start_position_ = start_position; }
	void __end_position(const D3DXVECTOR2& end_position) { end_position_ = end_position; }
	void __speed(f32 speed) { speed_ = speed; }
	void __rate(f32 rate) { rate_ = rate; }

private:
	ObjectMoveGround* object_move_ground_;
	D3DXVECTOR2 start_position_;
	D3DXVECTOR2 end_position_;
	f32 speed_;
	f32 rate_;
	DATA data_;
};

#endif	// _GIMMICK_MOVE_GROUND_H_

//---------------------------------- EOF --------------------------------------
