//*****************************************************************************
//
// object check point
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _OBJECT_CHECK_POINT_H_
#define _OBJECT_CHECK_POINT_H_

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
class ObjectCheckPoint : public Basic
{
public:
	// constructor
	ObjectCheckPoint(void);

	// destructor
	virtual ~ObjectCheckPoint(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// accessor
	void __position(const D3DXVECTOR2& position) { position_ = position; }
	const D3DXVECTOR2& __size(void) { return size_; }

private:
	static const D3DXVECTOR2 SIZE;
	static const u32 DIVISION_WIDTH;
	static const u32 DIVISION_HEIGHT;

	Sprite* object_check_point_;
	D3DXVECTOR2 position_;
	D3DXVECTOR2 size_;
};

#endif	// _OBJECT_CHECK_POINT_H_

//---------------------------------- EOF --------------------------------------
