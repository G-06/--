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
#ifndef _GIMMICK_LENS_H_
#define _GIMMICK_LENS_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "gimmick.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class ObjectLens;

//*****************************************************************************
// class definition
//*****************************************************************************
class GimmickLens : public Gimmick
{
public:
	struct DATA
	{
		D3DXVECTOR2 _move;
		D3DXVECTOR2 _shotvec;
		D3DXVECTOR2 _shotposition;
	};

	// constructor
	GimmickLens(void);

	// destructor
	virtual ~GimmickLens(void);

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
	void __shot_vec( u32 shotvec) { shot_vec_ = shotvec; }
	void __start_position(const D3DXVECTOR2& start_position) { start_position_ = start_position; }
	void __end_position(const D3DXVECTOR2& end_position) { end_position_ = end_position; }
	void __speed(f32 speed) { speed_ = speed; }
	void __rate(f32 rate) { rate_ = rate; }
	//bool __is_show(void) { return is_show_; }



private:
	ObjectLens* object_lens_;
	u32 shot_vec_;
	D3DXVECTOR2 start_position_;
	D3DXVECTOR2 end_position_;
	f32 speed_;
	f32 rate_;


	DATA data_;
};

#endif	// _GIMMICK_LENS_H_

//---------------------------------- EOF --------------------------------------
