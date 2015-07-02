//*****************************************************************************
//
// gimmick lens
//
// Author		: Haruki Saito
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "gimmick_lens.h"
#include "object/object_lens.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const u32 LENS_FORCE = 300;
const D3DXVECTOR2 LENS_PUSH_LENGTH = D3DXVECTOR2(140.0f,140.0f);
const D3DXVECTOR2 LENS_SIZE = D3DXVECTOR2(128.0f,128.0f);
//=============================================================================
// constructor
//=============================================================================
GimmickLens::GimmickLens(void)
	:Gimmick(TYPE_LENS)
	,shot_vec_(0)
	,start_position_(0.0f,0.0f)
	,end_position_(0.0f,0.0f)
	,speed_(0.0f)
	,rate_(0.0f)
{
	size_ = LENS_SIZE;
}

//=============================================================================
// destructor
//=============================================================================
GimmickLens::~GimmickLens(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool GimmickLens::Initialize(void)
{
	object_lens_ = new ObjectLens();
	object_lens_->Initialize();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void GimmickLens::Uninitialize(void)
{
	SafeRelease(object_lens_);
}

//=============================================================================
// update
//=============================================================================
void GimmickLens::Update(void)
{
	
	//object_lens_->Show(is_show_);
	object_lens_->Update();
	// ˆÚ“®—p
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
	
	switch(shot_vec_)
	{
	case 1:
		{
			
			data_._shotvec = D3DXVECTOR2(position_.x - LENS_FORCE,position_.y + LENS_FORCE) - position_;
			data_._shotposition = D3DXVECTOR2(position_.x - LENS_PUSH_LENGTH.x,position_.y + LENS_PUSH_LENGTH.y);
			
			break;
		}
	case 2:
		{
			data_._shotvec = D3DXVECTOR2(position_.x,position_.y + LENS_FORCE) - position_;
			data_._shotposition = D3DXVECTOR2(position_.x,position_.y - LENS_PUSH_LENGTH.y);
			break;
		}
	case 3:
		{
			data_._shotvec = D3DXVECTOR2(position_.x + LENS_FORCE,position_.y - LENS_FORCE) - position_;
			data_._shotposition = D3DXVECTOR2(position_.x + LENS_PUSH_LENGTH.x,position_.y - LENS_PUSH_LENGTH.y);
			break;
		}
	case 4:
		{
			data_._shotvec = D3DXVECTOR2(position_.x - LENS_FORCE,position_.y) - position_;
			data_._shotposition = D3DXVECTOR2(position_.x - LENS_PUSH_LENGTH.x,position_.y);
			break;
		}
	case 6:
		{
			data_._shotvec = D3DXVECTOR2(position_.x + LENS_FORCE,position_.y) - position_;
			data_._shotposition = D3DXVECTOR2(position_.x + LENS_PUSH_LENGTH.x,position_.y);
			break;
		}
	case 7:
		{
			data_._shotvec = D3DXVECTOR2(position_.x - LENS_FORCE,position_.y - LENS_FORCE) - position_;
			data_._shotposition = D3DXVECTOR2(position_.x - LENS_PUSH_LENGTH.x,position_.y - LENS_PUSH_LENGTH.y);
			break;
		}
	case 8:
		{
			data_._shotvec = D3DXVECTOR2(position_.x ,position_.y - LENS_FORCE) - position_;
			data_._shotposition = D3DXVECTOR2(position_.x,position_.y - LENS_PUSH_LENGTH.y);
			break;
		}
	case 9:
		{
			data_._shotvec = D3DXVECTOR2(position_.x + LENS_FORCE,position_.y - LENS_FORCE) - position_;
			data_._shotposition = D3DXVECTOR2(position_.x + LENS_PUSH_LENGTH.x,position_.y - LENS_PUSH_LENGTH.y);
			break;
		}
	}

}

//=============================================================================
// draw
//=============================================================================
void GimmickLens::Draw(void)
{
	object_lens_->__position(position_ - offset_position_);
	object_lens_->Draw();
}

//=============================================================================
// get pointer
//=============================================================================
void* GimmickLens::GetPointer(void)
{
	return &data_;
}

//---------------------------------- EOF --------------------------------------
