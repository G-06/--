//*****************************************************************************
//
// object start point
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "object_start_point.h"
#include "render/sprite.h"
#include "system/system.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 ObjectStartPoint::SIZE	= D3DXVECTOR2(128.0f,128.0f);
const u32 ObjectStartPoint::DIVISION_WIDTH	= 1;
const u32 ObjectStartPoint::DIVISION_HEIGHT	= 1;

//=============================================================================
// constructor
//=============================================================================
ObjectStartPoint::ObjectStartPoint(void)
	:object_start_point_(nullptr)
	,position_(0.0f,0.0f)
	,size_(0.0f,0.0f)
{
}

//=============================================================================
// destructor
//=============================================================================
ObjectStartPoint::~ObjectStartPoint(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool ObjectStartPoint::Initialize(void)
{
	object_start_point_ = new Sprite();
	object_start_point_->Initialize();
	object_start_point_->__point(Sprite::POINT_CENTER);
	object_start_point_->__division_width(DIVISION_WIDTH);
	object_start_point_->__division_height(DIVISION_HEIGHT);
	object_start_point_->__size(SIZE);
	object_start_point_->__texture_id(Texture::TEXTURE_ID_GAME_START_POINT);
	object_start_point_->SetParameter();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void ObjectStartPoint::Uninitialize(void)
{
	SafeRelease(object_start_point_);
}

//=============================================================================
// update
//=============================================================================
void ObjectStartPoint::Update(void)
{
}

//=============================================================================
// draw
//=============================================================================
void ObjectStartPoint::Draw(void)
{
	object_start_point_->__position(position_);
	object_start_point_->Draw();
}

//---------------------------------- EOF --------------------------------------
