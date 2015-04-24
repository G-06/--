//*****************************************************************************
//
// collision point
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "collision_point.h"

//=============================================================================
// constructor
//=============================================================================
CollisionPoint::CollisionPoint(void) :
Collision(TYPE_POINT)
{
}

//=============================================================================
// destructor
//=============================================================================
CollisionPoint::~CollisionPoint(void)
{
}

//=============================================================================
// is hit
//=============================================================================
bool CollisionPoint::IsHit(const Collision* collision)const
{
	return collision->IsHitPoint(position_);
}

//=============================================================================
// is hit point
//=============================================================================
bool CollisionPoint::IsHitPoint(const D3DXVECTOR2& position)const
{
	if((s32)position_.x == (s32)position.x && (s32)position_.y == (s32)position.y)
	{
		return true;
	}

	return false;
}

//=============================================================================
// is hit circle
//=============================================================================
bool CollisionPoint::IsHitCircle(const D3DXVECTOR2& position,const f32& radius)const
{
	f32 distance = (position_.x - position.x) * (position_.x - position.x) + (position_.y - position.y) * (position_.y - position.y);

	if(distance <= (radius * radius))
	{
		return true;
	}

	return false;
}

//=============================================================================
// is hit line
//=============================================================================
bool CollisionPoint::IsHitLine(const D3DXVECTOR2& position,const D3DXVECTOR2& start,const D3DXVECTOR2& end)const
{
	D3DXVECTOR2 vector_l = end - start;
	D3DXVECTOR2 vector_a = position_ - (start + position);
	D3DXVECTOR2 vector_b = position_ - (end + position);
	f32 cross = D3DXVec2CCW(&vector_l,&vector_a);

	if(cross <= 0.0001f || cross >= -0.0001f)
	{
		cross = 0.0f;
	}

	if(cross == 0.0f)
	{
		if(D3DXVec2Dot(&vector_a,&vector_l) >= 0 && D3DXVec2Length(&vector_l) >= D3DXVec2Length(&vector_a))
		{
			return true;
		}
	}

	return false;
}

//---------------------------------- EOF --------------------------------------
