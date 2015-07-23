//*****************************************************************************
//
// object goal point
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _OBJECT_GOAL_POINT_H_
#define _OBJECT_GOAL_POINT_H_

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
class ObjectGoalPoint : public Basic
{
public:
	// constructor
	ObjectGoalPoint(void);

	// destructor
	virtual ~ObjectGoalPoint(void);

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
	void __rotation(const f32& rotation) { rotation_ = rotation; }
	f32 __rotation(void) { return rotation_; }
	const D3DXVECTOR2& __size(void) { return size_; }

	f32 __rotation_luminescnce(void) { return rotation_luminescnce_; }
	void __rotation_luminescnce(const f32& rotation) {rotation_luminescnce_ = rotation; }
	f32 __alpha(void) {return alpha_;}
	void __alpha(const f32& alpha) {alpha_ = alpha;}

	void __alpha_speed(const f32& speed){alpha_speed_ = speed;}
	const f32 __alpha_speed(void){return alpha_speed_;}
	void InverseAlphaSpeed(void){alpha_speed_ *= -1;}

private:
	static const D3DXVECTOR2 SIZE;
	static const u32 DIVISION_WIDTH;
	static const u32 DIVISION_HEIGHT;

	Sprite* object_goal_point_;
	Sprite* object_goal_point_luminescnce_;

	D3DXVECTOR2 position_;
	D3DXVECTOR2 size_;
	f32 rotation_;
	f32 rotation_luminescnce_;
	f32 alpha_;
	f32 alpha_speed_;
};

#endif	// _OBJECT_GOAL_POINT_H_

//---------------------------------- EOF --------------------------------------
