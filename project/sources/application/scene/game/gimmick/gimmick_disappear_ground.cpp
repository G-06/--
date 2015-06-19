//*****************************************************************************
//
// gimmick disappear ground
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "gimmick_disappear_ground.h"
#include "object/object_disappear_ground.h"

//*****************************************************************************
// constant definition
//*****************************************************************************

//=============================================================================
// constructor
//=============================================================================
GimmickDisappearGround::GimmickDisappearGround(void)
	:Gimmick(TYPE_DISAPPEAR_GROUND)
	,frame_count_(0)
{
	size_ = D3DXVECTOR2(128.0f,128.0f);
}

//=============================================================================
// destructor
//=============================================================================
GimmickDisappearGround::~GimmickDisappearGround(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool GimmickDisappearGround::Initialize(void)
{
	object_disappear_ground_ = new ObjectDisappearGround();
	object_disappear_ground_->Initialize();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void GimmickDisappearGround::Uninitialize(void)
{
	SafeRelease(object_disappear_ground_);
}

//=============================================================================
// update
//=============================================================================
void GimmickDisappearGround::Update(void)
{
	frame_count_++;

	if(is_show_)
	{
		data_._is_hit = true;
		if(frame_count_ > appear_frame_)
		{
			is_show_ = false;
			frame_count_ = 0;
			data_._is_hit = false;
		}
	}
	else
	{
		if(frame_count_ > disappear_frame_)
		{
			is_show_ = true;
			frame_count_ = 0;
		}
	}

	object_disappear_ground_->Show(is_show_);
	object_disappear_ground_->Update();
}

//=============================================================================
// draw
//=============================================================================
void GimmickDisappearGround::Draw(void)
{
	object_disappear_ground_->__position(position_ - offset_position_);
	object_disappear_ground_->Draw();
}

//=============================================================================
// get pointer
//=============================================================================
void* GimmickDisappearGround::GetPointer(void)
{
	return &data_;
}

//---------------------------------- EOF --------------------------------------
