//*****************************************************************************
//
// collision map
//
// Author		: Haruki Saito
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _COLLISION_MAP_H_
#define _COLLISION_MAP_H_

//*****************************************************************************
// include
//*****************************************************************************
//#include "collision.h"

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

	// Initialize
	bool Initialize(void);

	// is hit
	bool IsHit(D3DXVECTOR2 playerpos,D3DXVECTOR2 oldplayerpos,D3DXVECTOR2 chippos,float playerlengthx,float playerlengthy,float chiplengthx,float chiplengthy);

	// accessor
	const D3DXVECTOR2&  __position(void)const { return pushposition_; }
	void __position(const D3DXVECTOR2& position) { position_ = position; }
	const D3DXVECTOR2& __vector(void) { return vector_; }
private:
	D3DXVECTOR2 position_;
	f32 pushlengthx_;
	f32 pushlengthy_;
	D3DXVECTOR2 pushposition_;
	D3DXMATRIX matrix_;
	D3DXVECTOR2 vector_;

};

#endif	// _COLLISION_LINE_H_

//---------------------------------- EOF --------------------------------------
