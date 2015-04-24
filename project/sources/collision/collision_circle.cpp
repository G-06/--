//*****************************************************************************
//
// collision circle
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "collision_circle.h"

//=============================================================================
// constructor
//=============================================================================
CollisionCircle::CollisionCircle(void) :
Collision(TYPE_CIRCLE)
{
}

//=============================================================================
// destructor
//=============================================================================
CollisionCircle::~CollisionCircle(void)
{
}

//=============================================================================
// is hit
//=============================================================================
bool CollisionCircle::IsHit(const Collision* collision)const
{
	return collision->IsHitCircle(position_,radius_);
}

//=============================================================================
// is hit point
//=============================================================================
bool CollisionCircle::IsHitPoint(const D3DXVECTOR2& position)const
{
	f32 distance = (position_.x - position.x) * (position_.x - position.x) + (position_.y - position.y) * (position_.y - position.y);

	if(distance <= (radius_ * radius_))
	{
		return true;
	}

	return false;
}

//=============================================================================
// is hit circle
//=============================================================================
bool CollisionCircle::IsHitCircle(const D3DXVECTOR2& position,const f32& radius)const
{
	f32 distance = (position_.x - position.x) * (position_.x - position.x) + (position_.y - position.y) * (position_.y - position.y);

	if(distance <= (radius_ + radius) * (radius_ + radius))
	{
		return true;
	}

	return false;
}

//=============================================================================
// is hit line
//=============================================================================
bool CollisionCircle::IsHitLine(const D3DXVECTOR2& position,const D3DXVECTOR2& start,const D3DXVECTOR2& end)const
{
	D3DXVECTOR2 vector_l = end - start;
	D3DXVECTOR2 vector_a = position_ - (start + position);
	D3DXVECTOR2 vector_b = position_ - (end + position);
	f32 distance = D3DXVec2CCW(&vector_l,&vector_a) / D3DXVec2Length(&vector_l);

	if(distance <= radius_)
	{
		if(D3DXVec2Dot(&vector_a,&vector_l) * D3DXVec2Dot(&vector_b,&vector_l) <= 0)
		{
			return true;
		}

		if(D3DXVec2Length(&vector_a) <= radius_ || D3DXVec2Length(&vector_b) <= radius_)
		{
			return true;
		}
	}

	return false;
}

//---------------------------------- EOF --------------------------------------
