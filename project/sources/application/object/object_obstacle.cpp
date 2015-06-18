//*****************************************************************************
//
// object obstacle
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "object_obstacle.h"
#include "render/sprite.h"
#include "system/system.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 ObjectObstacle::SIZE	= D3DXVECTOR2(128.0f,128.0f);
const u32 ObjectObstacle::DIVISION_WIDTH	= 1;
const u32 ObjectObstacle::DIVISION_HEIGHT	= 1;

//=============================================================================
// constructor
//=============================================================================
ObjectObstacle::ObjectObstacle(void)
	:object_obstacle_(nullptr)
	,position_(0.0f,0.0f)
	,size_(0.0f,0.0f)
{
}

//=============================================================================
// destructor
//=============================================================================
ObjectObstacle::~ObjectObstacle(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool ObjectObstacle::Initialize(void)
{
	object_obstacle_ = new Sprite();
	object_obstacle_->Initialize();
	object_obstacle_->__point(Sprite::POINT_CENTER);
	object_obstacle_->__division_width(DIVISION_WIDTH);
	object_obstacle_->__division_height(DIVISION_HEIGHT);
	object_obstacle_->__size(SIZE);
	object_obstacle_->__texture_id(Texture::TEXTURE_ID_GAME_START_POINT);
	object_obstacle_->SetParameter();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void ObjectObstacle::Uninitialize(void)
{
	SafeRelease(object_obstacle_);
}

//=============================================================================
// update
//=============================================================================
void ObjectObstacle::Update(void)
{
}

//=============================================================================
// draw
//=============================================================================
void ObjectObstacle::Draw(void)
{
	object_obstacle_->__position(position_);
	object_obstacle_->Draw();
}

//---------------------------------- EOF --------------------------------------
