//*****************************************************************************
//
// object goal point
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "object_goal_point.h"
#include "render/sprite.h"
#include "system/system.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 SCALE	= D3DXVECTOR2(1.1f,1.1f);
const D3DXVECTOR2 ObjectGoalPoint::SIZE	= D3DXVECTOR2(256.0f * SCALE.x,256.0f * SCALE.y);
const u32 ObjectGoalPoint::DIVISION_WIDTH	= 1;
const u32 ObjectGoalPoint::DIVISION_HEIGHT	= 1;

//=============================================================================
// constructor
//=============================================================================
ObjectGoalPoint::ObjectGoalPoint(void)
	:object_goal_point_(nullptr)
	,object_goal_point_luminescnce_(nullptr)
	,position_(0.0f,0.0f)
	,rotation_(0.0)
	,rotation_luminescnce_(0.0f)
	,alpha_(1.0f)
	,size_(0.0f,0.0f)
	,alpha_speed_(0.0f)
{
}

//=============================================================================
// destructor
//=============================================================================
ObjectGoalPoint::~ObjectGoalPoint(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool ObjectGoalPoint::Initialize(void)
{
	object_goal_point_ = new Sprite();
	object_goal_point_->Initialize();
	object_goal_point_->__point(Sprite::POINT_CENTER);
	object_goal_point_->__division_width(DIVISION_WIDTH);
	object_goal_point_->__division_height(DIVISION_HEIGHT);
	object_goal_point_->__size(SIZE);
	object_goal_point_->__texture_id(Texture::TEXTURE_ID_GAME_GOAL_POINT);
	object_goal_point_->SetParameter();

	object_goal_point_luminescnce_ = new Sprite();
	object_goal_point_luminescnce_->Initialize();
	object_goal_point_luminescnce_->__point(Sprite::POINT_CENTER);
	object_goal_point_luminescnce_->__division_width(DIVISION_WIDTH);
	object_goal_point_luminescnce_->__division_height(DIVISION_HEIGHT);
	object_goal_point_luminescnce_->__size(SIZE);
	object_goal_point_luminescnce_->__texture_id(Texture::TEXTURE_ID_GAME_GOAL_POINT_LUMINESCENCE);
	object_goal_point_luminescnce_->SetParameter();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void ObjectGoalPoint::Uninitialize(void)
{
	SafeRelease(object_goal_point_);
	SafeRelease(object_goal_point_luminescnce_);
}

//=============================================================================
// update
//=============================================================================
void ObjectGoalPoint::Update(void)
{
}

//=============================================================================
// draw
//=============================================================================
void ObjectGoalPoint::Draw(void)
{
	object_goal_point_->__position(position_);
	object_goal_point_->__rotation(rotation_);
	object_goal_point_->Draw();

	object_goal_point_luminescnce_->__color(D3DXCOLOR(1.0f,1.0f,1.0,alpha_));
	object_goal_point_luminescnce_->__position(position_);
	object_goal_point_luminescnce_->__rotation(rotation_);
	object_goal_point_luminescnce_->SetParameter();
	object_goal_point_luminescnce_->Draw();
	object_goal_point_luminescnce_->Draw();
}

//---------------------------------- EOF --------------------------------------
