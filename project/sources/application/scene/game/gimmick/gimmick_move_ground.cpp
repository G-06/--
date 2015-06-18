//*****************************************************************************
//
// gimmick move ground
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "gimmick_move_ground.h"
#include "object/object_move_ground.h"

//*****************************************************************************
// constant definition
//*****************************************************************************

//=============================================================================
// constructor
//=============================================================================
GimmickMoveGround::GimmickMoveGround(void)
	:Gimmick(TYPE_MOVE_GROUND)
	,start_position_(0.0f,0.0f)
	,end_position_(0.0f,0.0f)
	,speed_(0.0f)
	,rate_(0.0f)
{
	size_ = D3DXVECTOR2(128.0f,128.0f);
}

//=============================================================================
// destructor
//=============================================================================
GimmickMoveGround::~GimmickMoveGround(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool GimmickMoveGround::Initialize(void)
{
	object_move_ground_ = new ObjectMoveGround();
	object_move_ground_->Initialize();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void GimmickMoveGround::Uninitialize(void)
{
	SafeRelease(object_move_ground_);
}

//=============================================================================
// update
//=============================================================================
void GimmickMoveGround::Update(void)
{
	object_move_ground_->Update();

	D3DXVECTOR2 vector = end_position_ - start_position_;

	data_._move = position_;

	rate_ += speed_;
	if(rate_ < 0.0f)
	{
		rate_ = 0.0f;
		speed_ *= -1;
	}

	if(rate_ > 1.0f)
	{
		rate_ = 1.0f;
		speed_ *= -1;
	}

	position_ = start_position_ + vector * rate_;
	data_._move = position_ - data_._move;
}

//=============================================================================
// draw
//=============================================================================
void GimmickMoveGround::Draw(void)
{
	object_move_ground_->__position(position_ - offset_position_);
	object_move_ground_->Draw();
}

//=============================================================================
// get pointer
//=============================================================================
void* GimmickMoveGround::GetPointer(void)
{
	return &data_;
}

//---------------------------------- EOF --------------------------------------
