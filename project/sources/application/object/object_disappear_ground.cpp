//*****************************************************************************
//
// object disappear ground
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "object_disappear_ground.h"
#include "render/sprite.h"
#include "system/system.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 ObjectDisappearGround::SIZE	= D3DXVECTOR2(256.0f,64.0f);
const u32 ObjectDisappearGround::DIVISION_WIDTH	= 1;
const u32 ObjectDisappearGround::DIVISION_HEIGHT	= 1;

//=============================================================================
// constructor
//=============================================================================
ObjectDisappearGround::ObjectDisappearGround(void)
	:object_disappear_ground_(nullptr)
	,position_(0.0f,0.0f)
	,size_(0.0f,0.0f)
	,frame_count_(0)
	,alpha_(1.0f)
	,is_show_(true)
	,show_frame_(60)
	,is_appear_(true)
{
}

//=============================================================================
// destructor
//=============================================================================
ObjectDisappearGround::~ObjectDisappearGround(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool ObjectDisappearGround::Initialize(void)
{
	object_disappear_ground_ = new Sprite();
	object_disappear_ground_->Initialize();
	object_disappear_ground_->__point(Sprite::POINT_CENTER);
	object_disappear_ground_->__division_width(DIVISION_WIDTH);
	object_disappear_ground_->__division_height(DIVISION_HEIGHT);
	object_disappear_ground_->__size(SIZE);
	object_disappear_ground_->__texture_id(Texture::TEXTURE_ID_DISAPPEAR_GROUND);
	object_disappear_ground_->SetParameter();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void ObjectDisappearGround::Uninitialize(void)
{
	SafeRelease(object_disappear_ground_);
}

//=============================================================================
// update
//=============================================================================
void ObjectDisappearGround::Update(void)
{
	if(frame_count_ < show_frame_)
	{
		frame_count_++;
		is_appear_ = true;

		if(is_show_)
		{
			alpha_ = (f32)frame_count_ / (f32)show_frame_;
		}
		else
		{
			alpha_ = 1.0f - (f32)frame_count_ / (f32)show_frame_;
		}

		if(alpha_ >= 1.0f)
		{
			alpha_ = 1.0f;
		}

		if(alpha_ <= 0.0f)
		{
			alpha_ = 0.0f;
			is_appear_ = false;
		}

		object_disappear_ground_->__color(D3DXCOLOR(1.0f,1.0f,1.0f,alpha_));
		object_disappear_ground_->SetParameter();
	}
}

//=============================================================================
// draw
//=============================================================================
void ObjectDisappearGround::Draw(void)
{
	object_disappear_ground_->__position(position_);
	object_disappear_ground_->Draw();
}

//=============================================================================
// show
//=============================================================================
void ObjectDisappearGround::Show(bool is_show)
{
	if(is_show_ != is_show)
	{
		is_show_ = is_show;
		frame_count_ = 0;
	}
}

//---------------------------------- EOF --------------------------------------
