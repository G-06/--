//*****************************************************************************
//
// collision line
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "collision_line.h"

//=============================================================================
// constructor
//=============================================================================
CollisionLine::CollisionLine(void) :
Collision(TYPE_LINE)
{
}

//=============================================================================
// destructor
//=============================================================================
CollisionLine::~CollisionLine(void)
{
}

//=============================================================================
// is hit
//=============================================================================
bool CollisionLine::IsHit(const Collision* collision)const
{
	return collision->IsHitLine(position_,start_,end_);
}

//=============================================================================
// is hit point
//=============================================================================
bool CollisionLine::IsHitPoint(const D3DXVECTOR2& position)const
{
	D3DXVECTOR2 vector_l = end_ - start_;
	D3DXVECTOR2 vector_a = position - (start_ + position_);
	D3DXVECTOR2 vector_b = position - (end_ + position_);
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

//=============================================================================
// is hit circle
//=============================================================================
bool CollisionLine::IsHitCircle(const D3DXVECTOR2& position,const f32& radius)const
{
	D3DXVECTOR2 vector_l = end_ - start_;
	D3DXVECTOR2 vector_a = position - (start_ + position_);
	D3DXVECTOR2 vector_b = position - (end_ + position_);
	f32 distance = D3DXVec2CCW(&vector_l,&vector_a) / D3DXVec2Length(&vector_l);

	if(distance <= radius)
	{
		if(D3DXVec2Dot(&vector_a,&vector_l) * D3DXVec2Dot(&vector_b,&vector_l) <= 0)
		{
			return true;
		}

		if(D3DXVec2Length(&vector_a) <= radius || D3DXVec2Length(&vector_b) <= radius)
		{
			return true;
		}
	}

	return false;
}

//=============================================================================
// is hit line
//=============================================================================
bool CollisionLine::IsHitLine(const D3DXVECTOR2& position,const D3DXVECTOR2& start,const D3DXVECTOR2& end)const
{
	D3DXVECTOR2 vector_a = end_ - start_;
	D3DXVECTOR2 vector_b = end - start;
	D3DXVECTOR2 vector_c = start - start_;

	float cross_a_b = D3DXVec2CCW(&vector_a,&vector_b);

	if(cross_a_b == 0.0f)
	{
		return false;
	}

	float cross_c_a = D3DXVec2CCW(&vector_c,&vector_a);
	float cross_c_b = D3DXVec2CCW(&vector_c,&vector_b);

	float t_a = cross_c_b / cross_a_b;
	float t_b = cross_c_a / cross_a_b;
	const f32 eps = 0.00001f;

	if(t_a + eps < 0 || t_a - eps > 1 || t_b + eps < 0 || t_b - eps > 1)
	{
		return false;
	}

	return true;
}

//---------------------------------- EOF --------------------------------------
