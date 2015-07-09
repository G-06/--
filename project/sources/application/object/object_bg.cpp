//*****************************************************************************
//
// logo bg
//
// Author		: taichi kitazawa
//				: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "object_bg.h"
#include "render/sprite.h"
#include "system/system.h"

//=============================================================================
// constructor
//=============================================================================
ObjectBg::ObjectBg(void)
{
}

//=============================================================================
// destructor
//=============================================================================
ObjectBg::~ObjectBg(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool ObjectBg::Initialize(void)
{
	bg_ = new Sprite();
	bg_->Initialize();
//	bg_->__size(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width(),(f32)GET_SYSTEM.__window()->__height()));
	bg_->__size(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width(),(f32)GET_SYSTEM.__window()->__width()));
	bg_->__position(D3DXVECTOR2(0.0f,0.0f));
	bg_->__color(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	bg_->SetParameter();

	uv_x_ = D3DXVECTOR2(0.0f,1.0f);
	uv_y_ = D3DXVECTOR2(0.0f,1.0f);
	move_ = D3DXVECTOR2(0.0f,0.0f);

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void ObjectBg::Uninitialize(void)
{
	SafeRelease(bg_);
}

//=============================================================================
// update
//=============================================================================
void ObjectBg::Update(void)
{
	uv_x_.x+=move_.x;
	uv_x_.y+=move_.x;
	uv_y_.x+=move_.y;
	uv_y_.y+=move_.y;

	bg_->__left(uv_x_.x);
	bg_->__right(uv_x_.y);
	bg_->__top(uv_y_.x);
	bg_->__bottom(uv_y_.y);

	bg_->SetParameter();
	move_ = D3DXVECTOR2(0.0f,0.0f);
}

//=============================================================================
// draw
//=============================================================================
void ObjectBg::Draw(void)
{
	bg_->Draw();
}


//=============================================================================
//テクスチャ設置
//=============================================================================
void ObjectBg::__SetTexture(Texture::TEXTURE_ID texture)
{
	bg_->__texture_id(texture);
	bg_->SetParameter();
}

void ObjectBg::ReSetUv(void)
{
	uv_x_ = D3DXVECTOR2(0.0f,1.0f);
	uv_y_ = D3DXVECTOR2(0.0f,1.0f);
	bg_->__left(uv_x_.x);
	bg_->__right(uv_x_.y);
	bg_->__top(uv_y_.x);
	bg_->__bottom(uv_y_.y);
	bg_->SetParameter();
}

void ObjectBg::__Set_size(D3DXVECTOR2 size)
{
	bg_->__size(size);
	bg_->SetParameter();
}


//---------------------------------- EOF --------------------------------------
