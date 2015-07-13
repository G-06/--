//*****************************************************************************
//
// obj new record
//
// Author		: taichi kitazawa
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "object_newrecord.h"
#include "render/sprite.h"
#include "system/system.h"

const static D3DXVECTOR2 DEFAULT_POSITION = D3DXVECTOR2(0.0f,-100.0f);
const static D3DXVECTOR2 DEFAULT_SIZE = D3DXVECTOR2(512.0f,128.0f);

//=============================================================================
// constructor
//=============================================================================
ObjectNewRecord::ObjectNewRecord(void)
{
}

//=============================================================================
// destructor
//=============================================================================
ObjectNewRecord::~ObjectNewRecord(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool ObjectNewRecord::Initialize(void)
{
	position_ = DEFAULT_POSITION;

	sprite_ = new Sprite();
	sprite_->Initialize();
	sprite_->__point(Sprite::POINT_CENTER);
	sprite_->__size(DEFAULT_SIZE);
	sprite_->__position(position_);
	sprite_->__texture_id(Texture::TEXTURE_ID_GAME_STRING_NEW_RECORD);
	sprite_->SetParameter();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void ObjectNewRecord::Uninitialize(void)
{
	SafeRelease(sprite_);
}

//=============================================================================
// update
//=============================================================================
void ObjectNewRecord::Update(void)
{
	sprite_->__position(position_);
	sprite_->SetParameter();
}

//=============================================================================
// draw
//=============================================================================
void ObjectNewRecord::Draw(void)
{
	sprite_->Draw();
}

//=============================================================================
// SetPosition
//=============================================================================
void ObjectNewRecord::__set_position(D3DXVECTOR2 position)
{
	position_=position;
	sprite_->__position(position_);
}

//---------------------------------- EOF --------------------------------------
