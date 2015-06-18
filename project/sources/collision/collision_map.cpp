//*****************************************************************************
//
// collision Map
//
// Author		: Haruki Saitou
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "collision_map.h"

//=============================================================================
// constructor
//=============================================================================
CollisionMap::CollisionMap(void)
{
}

//=============================================================================
// destructor
//=============================================================================
CollisionMap::~CollisionMap(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool CollisionMap::Initialize(void)
{
	position_				= D3DXVECTOR2(0, 0);
	pushposition_			= D3DXVECTOR2(0, 0);
	pushlengthx_			= 0;
	pushlengthy_			= 0;
	return true;
}

//=============================================================================
// is hit
//=============================================================================
bool CollisionMap::IsHit(D3DXVECTOR2 playerpos,D3DXVECTOR2 oldplayerpos,D3DXVECTOR2 chippos,float playerlengthx,float playerlengthy,float chiplengthx,float chiplengthy)
{
	f32 a,b,c;

	//プレイヤーのベクトルを求める
	D3DXVECTOR2 playerAxisX,playerAxisY,chipAxisX,chipAxisY,v;
	D3DXMATRIX translationMatrix, rotationMatrix;

	D3DXMatrixIdentity(&matrix_);
	D3DXMatrixTranslation(&translationMatrix,playerpos.x,playerpos.y,0);
	D3DXMatrixMultiply(&matrix_,&matrix_,&translationMatrix);
	playerAxisX.x = matrix_._11;
	playerAxisX.y = matrix_._12;

	playerAxisY.x = matrix_._21;
	playerAxisY.y = matrix_._22;

	// 対象のベクトルを求める
	D3DXMatrixIdentity(&matrix_);
	D3DXMatrixTranslation(&translationMatrix,chippos.x,chippos.y,0);
	D3DXMatrixMultiply(&matrix_,&matrix_,&translationMatrix);

	chipAxisX.x = matrix_._11;
	chipAxisX.y = matrix_._12;
	chipAxisY.x = matrix_._21;
	chipAxisY.y = matrix_._22;
	
	// あたり判定処理（当たってない場合抜ける）
	v = playerpos - chippos;
	a = playerlengthx;
	b = abs(D3DXVec2Dot(&(chipAxisX * chiplengthx),&playerAxisX))+
		abs(D3DXVec2Dot(&(chipAxisY * chiplengthy),&playerAxisX));
	c = abs(D3DXVec2Dot(&v, &playerAxisX));
	f32 maxLengthX = playerlengthx + chiplengthx;
	if( (a + b) < c)
	{
		
		return false;
		
	}
	a = playerlengthy;
	b = abs(D3DXVec2Dot(&(chipAxisX * chiplengthx),&playerAxisY))+
		abs(D3DXVec2Dot(&(chipAxisY * chiplengthy),&playerAxisY));
	c = abs(D3DXVec2Dot(&v, &playerAxisY));
	f32 maxLengthY = playerlengthy + chiplengthy;
	if( (a + b) < c)
	{
		return false;
	}
	a = chiplengthx;
	b = abs(D3DXVec2Dot(&(playerAxisX * playerlengthx),&chipAxisX))+
		abs(D3DXVec2Dot(&(playerAxisY * playerlengthy),&chipAxisX));
	c = abs(D3DXVec2Dot(&v, &chipAxisX));
	if( (a + b) < c)
	{
		return false;
	}
	a = chiplengthy;
	b = abs(D3DXVec2Dot(&(playerAxisX * playerlengthx),&chipAxisY))+
		abs(D3DXVec2Dot(&(playerAxisY * playerlengthy),&chipAxisY));
	c = abs(D3DXVec2Dot(&v, &chipAxisY));
	if( (a + b) < c)
	{
		return false;
	}
	// めり込み距離の計算
	c = abs(D3DXVec2Dot(&v, &chipAxisX));
	pushlengthx_ = maxLengthX - c;
	c = abs(D3DXVec2Dot(&v, &chipAxisY));
	pushlengthy_ = maxLengthY - c;

	// 押し出したポジションの計算
	D3DXVECTOR2 pv;
	pv = playerpos - oldplayerpos;
	if(pv.x < 0)
	{
	}
	else if(pv.x == 0)
	{
		pushlengthx_ = 0;
	}
	else if(pv.x > 0)
	{
		pushlengthx_ *= -1;
	}
	if(pv.y < 0)
	{
	}
	else if(pv.y == 0)
	{
		pushlengthy_ = 0;
	}
	else if(pv.y > 0)
	{
		pushlengthy_ *= -1;
	}
	if(abs(pv.x)>abs(pv.y))
	{
		pushlengthy_ = 0;
	}
	else if(abs(pv.y)>abs(pv.x))
	{
		pushlengthx_ = 0;
	}

	pushposition_ = D3DXVECTOR2(playerpos.x + pushlengthx_,playerpos.y + pushlengthy_ - 0.1f);

	return true;
}


//---------------------------------- EOF --------------------------------------
