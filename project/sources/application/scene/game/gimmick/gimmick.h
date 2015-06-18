//*****************************************************************************
//
// gimmick
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _GIMMICK_H_
#define _GIMMICK_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************

//*****************************************************************************
// class definition
//*****************************************************************************
class Gimmick : public Basic
{
public:
	enum TYPE
	{
		TYPE_START_POINT = 0,
		TYPE_CHECK_POINT,
		TYPE_GOAL_POINT,
		TYPE_OBSTACLE,
		TYPE_DISAPPEAR_GROUND,
		TYPE_MOVE_GROUND,
		TYPE_MAX,
	};

	// constructor
	Gimmick(TYPE type);

	// destructor
	virtual ~Gimmick(void);

	// initialize
	virtual bool Initialize(void);

	// uninitialize
	virtual void Uninitialize(void);

	// update
	virtual void Update(void);

	// draw
	virtual void Draw(void);

	// get pointer
	virtual void* GetPointer(void) { return nullptr; }

	// accessor
	void __position(const D3DXVECTOR2& position) { position_ = position; }
	const D3DXVECTOR2& __position(void) { return position_; }
	const D3DXVECTOR2& __size(void) { return size_; }
	void __offset_position(const D3DXVECTOR2& offset_position) { offset_position_ = offset_position; }
	TYPE __type(void)const { return type_; }

protected:
	D3DXVECTOR2 position_;
	D3DXVECTOR2 offset_position_;
	D3DXVECTOR2 size_;
	TYPE type_;
};

#endif	// _OBJECT_START_POINT_H_

//---------------------------------- EOF --------------------------------------
