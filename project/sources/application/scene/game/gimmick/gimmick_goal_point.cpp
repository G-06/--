//*****************************************************************************
//
// gimmick goal point
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "gimmick_goal_point.h"
#include "object/object_goal_point.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 GOAL_SIZE	= D3DXVECTOR2(200.0f,200.0f);
const f32 GOAL_ROTATION_ADD = 0.005f;
// luminesceneの点滅数値
const f32 LUMINESCENCE_ALPHA_MAX = 1.1f;
const f32 LUMINESCENCE_ALPHA_MIN = 0.3f;
const f32 LUMINESCENCE_ALPHA_SPEED = -0.015f;

//=============================================================================
// constructor
//=============================================================================
GimmickGoalPoint::GimmickGoalPoint(void)
	:Gimmick(TYPE_GOAL_POINT)
{
	size_ = GOAL_SIZE;
}

//=============================================================================
// destructor
//=============================================================================
GimmickGoalPoint::~GimmickGoalPoint(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool GimmickGoalPoint::Initialize(void)
{
	object_goal_point_ = new ObjectGoalPoint();
	object_goal_point_->Initialize();
	object_goal_point_->__alpha_speed(LUMINESCENCE_ALPHA_SPEED);

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void GimmickGoalPoint::Uninitialize(void)
{
	SafeRelease(object_goal_point_);
}

//=============================================================================
// update
//=============================================================================
void GimmickGoalPoint::Update(void)
{
	// update
	object_goal_point_->Update();

	// rotation加算
	f32 old_rotation = object_goal_point_->__rotation();
	f32 temp_rotation = old_rotation + GOAL_ROTATION_ADD;

	// normalize
	if( temp_rotation > D3DX_PI ){
		temp_rotation -= ( 2.0f * D3DX_PI );
	}
	if( temp_rotation < -(D3DX_PI) ){
		temp_rotation += ( 2.0f * D3DX_PI );
	}

	object_goal_point_->__rotation(temp_rotation);

	// アルファ取得
	f32 alpha = object_goal_point_->__alpha();

	// アルファ値加算
	alpha += object_goal_point_->__alpha_speed();

	if( alpha > LUMINESCENCE_ALPHA_MAX )
	{
		alpha = LUMINESCENCE_ALPHA_MAX;
		object_goal_point_->InverseAlphaSpeed();
	}
	else if( alpha < LUMINESCENCE_ALPHA_MIN)
	{
		alpha  = LUMINESCENCE_ALPHA_MIN;
		object_goal_point_->InverseAlphaSpeed();
	}

	// 設定
	object_goal_point_->__alpha(alpha);
}

//=============================================================================
// draw
//=============================================================================
void GimmickGoalPoint::Draw(void)
{
	object_goal_point_->__position(position_ - offset_position_);
	object_goal_point_->Draw();
}

//---------------------------------- EOF --------------------------------------
