//*****************************************************************************
//
// gimmick check point
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "gimmick_check_point.h"
#include "object/object_check_point.h"

//*****************************************************************************
// constant definition
//*****************************************************************************

//=============================================================================
// constructor
//=============================================================================
GimmickCheckPoint::GimmickCheckPoint(void)
	:Gimmick(TYPE_CHECK_POINT)
	,priority_(0)
{
}

//=============================================================================
// destructor
//=============================================================================
GimmickCheckPoint::~GimmickCheckPoint(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool GimmickCheckPoint::Initialize(void)
{
	object_check_point_ = new ObjectCheckPoint();
	object_check_point_->Initialize();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void GimmickCheckPoint::Uninitialize(void)
{
	SafeRelease(object_check_point_);
}

//=============================================================================
// update
//=============================================================================
void GimmickCheckPoint::Update(void)
{
	object_check_point_->Update();
}

//=============================================================================
// draw
//=============================================================================
void GimmickCheckPoint::Draw(void)
{
	object_check_point_->__position(position_ - offset_position_);
	object_check_point_->Draw();
}

//---------------------------------- EOF --------------------------------------
