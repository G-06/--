//*****************************************************************************
//
// object obstacle
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _OBJECT_OBSTACLE_H_
#define _OBJECT_OBSTACLE_H_

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
class ObjectObstacle : public Basic
{
public:
	// constructor
	ObjectObstacle(void);

	// destructor
	virtual ~ObjectObstacle(void);

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

	Sprite* object_obstacle_;
	D3DXVECTOR2 position_;
	D3DXVECTOR2 size_;
};

#endif	// _OBJECT_OBSTACLE_H_

//---------------------------------- EOF --------------------------------------
