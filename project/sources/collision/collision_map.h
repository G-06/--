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
class CollisionMap
{
public:
	// constructor
	CollisionMap(void);

	// destructor
	virtual ~CollisionMap(void);

	// is hit
	bool IsHit(D3DXVECTOR2 playerpos,D3DXVECTOR2 oldplayerpos,D3DXVECTOR2 chippos,float playerlengthx,float playerlengthy,float chiplengthx,float chiplengthy);
	

	// accessor
	const D3DXVECTOR2&  __position(void)const { return position_; }
	void __position(const D3DXVECTOR2& position) { position_ = position; }

private:
	D3DXVECTOR2 position_;
	float pushlengthx_;
	float pushlengthy_;
	D3DXVECTOR2 pushposition_;
	D3DXMATRIX matrix_;

};

#endif	// _COLLISION_LINE_H_

//---------------------------------- EOF --------------------------------------
