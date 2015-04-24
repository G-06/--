//*****************************************************************************
//
// collision circle
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _COLLISION_CIRCLE_H_
#define _COLLISION_CIRCLE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "collision.h"

//*****************************************************************************
// class definition
//*****************************************************************************
class CollisionCircle : public Collision
{
public:
	// constructor
	CollisionCircle(void);

	// destructor
	virtual ~CollisionCircle(void);

	// is hit
	bool IsHit(const Collision* collision)const;

	// is hit point
	bool IsHitPoint(const D3DXVECTOR2& position)const;

	// is hit circle
	bool IsHitCircle(const D3DXVECTOR2& position,const f32& radius)const;

	// is hit line
	bool IsHitLine(const D3DXVECTOR2& position,const D3DXVECTOR2& start,const D3DXVECTOR2& end)const;

	// accessor
	const D3DXVECTOR2&  __position(void)const { return position_; }
	void __position(const D3DXVECTOR2& position) { position_ = position; }
	const f32& __radius(void)const { return radius_; }
	void __radius(const f32& radius) { radius_ = radius; }

private:
	D3DXVECTOR2 position_;
	f32 radius_;
};

#endif	// _COLLISION_CIRCLE_H_

//---------------------------------- EOF --------------------------------------
