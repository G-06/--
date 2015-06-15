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
const D3DXVECTOR2 ObjectGoalPoint::SIZE	= D3DXVECTOR2(128.0f,128.0f);
const u32 ObjectGoalPoint::DIVISION_WIDTH	= 1;
const u32 ObjectGoalPoint::DIVISION_HEIGHT	= 1;

//=============================================================================
// constructor
//=============================================================================
ObjectGoalPoint::ObjectGoalPoint(void)
	:object_goal_point_(nullptr)
	,position_(0.0f,0.0f)
	,size_(0.0f,0.0f)
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
	object_goal_point_->__texture_id(Texture::TEXTURE_ID_GAME_START_POINT);
	object_goal_point_->SetParameter();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void ObjectGoalPoint::Uninitialize(void)
{
	SafeRelease(object_goal_point_);
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
	object_goal_point_->Draw();
}

//---------------------------------- EOF --------------------------------------
