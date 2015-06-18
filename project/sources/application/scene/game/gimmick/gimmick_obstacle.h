//*****************************************************************************
//
// gimmick obstacle
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _GIMMICK_OBSTACLE_H_
#define _GIMMICK_OBSTACLE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "gimmick.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class ObjectObstacle;

//*****************************************************************************
// class definition
//*****************************************************************************
class GimmickObstacle : public Gimmick
{
public:
	// constructor
	GimmickObstacle(void);

	// destructor
	virtual ~GimmickObstacle(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// accessor
	void __start_position(const D3DXVECTOR2& start_position) { start_position_ = start_position; }
	void __end_position(const D3DXVECTOR2& end_position) { end_position_ = end_position; }
	void __speed(f32 speed) { speed_ = speed; }
	void __rate(f32 rate) { rate_ = rate; }

private:
	ObjectObstacle* object_obstacle_;
	D3DXVECTOR2 start_position_;
	D3DXVECTOR2 end_position_;
	f32 speed_;
	f32 rate_;

};

#endif	// _GIMMICK_OBSTACLE_H_

//---------------------------------- EOF --------------------------------------
