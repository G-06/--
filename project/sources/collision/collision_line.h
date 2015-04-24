//*****************************************************************************
//
// collision line
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _COLLISION_LINE_H_
#define _COLLISION_LINE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "collision.h"

//*****************************************************************************
// class definition
//*****************************************************************************
class CollisionLine : public Collision
{
public:
	// constructor
	CollisionLine(void);

	// destructor
	virtual ~CollisionLine(void);

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
	const D3DXVECTOR2&  __start(void)const { return start_; }
	void __start(const D3DXVECTOR2& start) { start_ = start; }
	const D3DXVECTOR2&  __end(void)const { return end_; }
	void __end(const D3DXVECTOR2& end) { end_ = end; }

private:
	D3DXVECTOR2 position_;
	D3DXVECTOR2 start_;
	D3DXVECTOR2 end_;
};

#endif	// _COLLISION_LINE_H_

//---------------------------------- EOF --------------------------------------
