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

	// rotation‰ÁŽZ
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
