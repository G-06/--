//*****************************************************************************
//
// collision
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _COLLISION_H_
#define _COLLISION_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"

//*****************************************************************************
// class definition
//*****************************************************************************
class Collision : public Basic
{
public:
	enum TYPE
	{
		TYPE_POINT = 0,
		TYPE_CIRCLE,
		TYPE_LINE,
		TYPE_MAP,
		TYPE_MAX
	};

	// constructor
	Collision(const TYPE& type);

	// destructor
	virtual ~Collision(void);

	// initialize
	bool Initialize(void) { return true; }

	// uninitialize
	void Uninitialize(void) {}

	// is hit
	virtual bool IsHit(const Collision* collision)const = 0;

	// is hit point
	virtual bool IsHitPoint(const D3DXVECTOR2& position)const = 0;

	// is hit circle
	virtual bool IsHitCircle(const D3DXVECTOR2& position,const f32& radius)const = 0;

	// is hit line
	virtual bool IsHitLine(const D3DXVECTOR2& position,const D3DXVECTOR2& start,const D3DXVECTOR2& end)const = 0;

	// accessor
	const TYPE& __type(void)const { return type_; }

protected:
	
private:
	TYPE type_;
};

#endif	// _COLLISION_H_

//---------------------------------- EOF --------------------------------------
