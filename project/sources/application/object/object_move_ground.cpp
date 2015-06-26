//*****************************************************************************
//
// object move ground
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "object_move_ground.h"
#include "render/sprite.h"
#include "system/system.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 ObjectMoveGround::SIZE	= D3DXVECTOR2(256.0f,64.0f);
const u32 ObjectMoveGround::DIVISION_WIDTH	= 1;
const u32 ObjectMoveGround::DIVISION_HEIGHT	= 1;

//=============================================================================
// constructor
//=============================================================================
ObjectMoveGround::ObjectMoveGround(void)
	:object_move_ground_(nullptr)
	,position_(0.0f,0.0f)
	,size_(0.0f,0.0f)
{
}

//=============================================================================
// destructor
//=============================================================================
ObjectMoveGround::~ObjectMoveGround(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool ObjectMoveGround::Initialize(void)
{
	object_move_ground_ = new Sprite();
	object_move_ground_->Initialize();
	object_move_ground_->__point(Sprite::POINT_CENTER);
	object_move_ground_->__division_width(DIVISION_WIDTH);
	object_move_ground_->__division_height(DIVISION_HEIGHT);
	object_move_ground_->__size(SIZE);
	object_move_ground_->__texture_id(Texture::TEXTURE_ID_MOVE_GROUND);
	object_move_ground_->SetParameter();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void ObjectMoveGround::Uninitialize(void)
{
	SafeRelease(object_move_ground_);
}

//=============================================================================
// update
//=============================================================================
void ObjectMoveGround::Update(void)
{
}

//=============================================================================
// draw
//=============================================================================
void ObjectMoveGround::Draw(void)
{
	object_move_ground_->__position(position_);
	object_move_ground_->Draw();
}

//---------------------------------- EOF --------------------------------------
