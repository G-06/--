//*****************************************************************************
//
// object check point
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "object_check_point.h"
#include "render/sprite.h"
#include "system/system.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 ObjectCheckPoint::SIZE	= D3DXVECTOR2(150.0f,230.0f);
const u32 ObjectCheckPoint::DIVISION_WIDTH	= 1;
const u32 ObjectCheckPoint::DIVISION_HEIGHT	= 1;

//=============================================================================
// constructor
//=============================================================================
ObjectCheckPoint::ObjectCheckPoint(void)
	:object_check_point_(nullptr)
	,position_(0.0f,0.0f)
	,size_(0.0f,0.0f)
{
}

//=============================================================================
// destructor
//=============================================================================
ObjectCheckPoint::~ObjectCheckPoint(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool ObjectCheckPoint::Initialize(void)
{
	object_check_point_ = new Sprite();
	object_check_point_->Initialize();
	object_check_point_->__point(Sprite::POINT_CENTER);
	object_check_point_->__division_width(DIVISION_WIDTH);
	object_check_point_->__division_height(DIVISION_HEIGHT);
	object_check_point_->__size(SIZE);
	object_check_point_->__texture_id(Texture::TEXTURE_ID_GAME_CHECK_POINT);
	object_check_point_->__division_width(2);
	object_check_point_->__division_height(1);
	object_check_point_->__index(1);
	object_check_point_->SetParameter();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void ObjectCheckPoint::Uninitialize(void)
{
	SafeRelease(object_check_point_);
}

//=============================================================================
// update
//=============================================================================
void ObjectCheckPoint::Update(void)
{
}

//=============================================================================
// draw
//=============================================================================
void ObjectCheckPoint::Draw(void)
{
	object_check_point_->__position(position_);
	object_check_point_->Draw();
}

void ObjectCheckPoint::Hit(void)
{
	object_check_point_->__index(0);
	object_check_point_->SetParameter();
}



//---------------------------------- EOF --------------------------------------
