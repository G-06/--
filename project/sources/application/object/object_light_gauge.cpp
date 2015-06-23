//*****************************************************************************
//
// object light gauge
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "object_light_gauge.h"
#include "render/sprite.h"
#include "system/system.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 ObjectLightGauge::GAUGE_SIZE = D3DXVECTOR2(320.0f,127.0f);
const D3DXVECTOR2 ObjectLightGauge::GAUGE_POSITION = D3DXVECTOR2(70.0f,0.0f);
const D3DXVECTOR2 ObjectLightGauge::GAUGE_FRAME_SIZE = D3DXVECTOR2(430.0f,127.0f);

//=============================================================================
// constructor
//=============================================================================
ObjectLightGauge::ObjectLightGauge(void)
	:gauge_(nullptr)
	,gauge_frame_(nullptr)
	,gauge_back_(nullptr)
	,position_(0.0f,0.0f)
	,rate_(100.0f)
{
}

//=============================================================================
// destructor
//=============================================================================
ObjectLightGauge::~ObjectLightGauge(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool ObjectLightGauge::Initialize(void)
{
	gauge_ = new Sprite();
	gauge_->Initialize();
	gauge_->__point(Sprite::POINT_LEFT_MIDDLE);
	gauge_->__size(GAUGE_SIZE);
	gauge_->__texture_id(Texture::TEXTURE_ID_GAME_LIGHT_GAUGE);
	gauge_->SetParameter();

	gauge_back_ = new Sprite();
	gauge_back_->Initialize();
	gauge_back_->__point(Sprite::POINT_LEFT_MIDDLE);
	gauge_back_->__size(GAUGE_FRAME_SIZE);
	gauge_back_->__texture_id(Texture::TEXTURE_ID_GAME_LIGHT_GAUGE_BACK);
	gauge_back_->SetParameter();

	gauge_frame_ = new Sprite();
	gauge_frame_->Initialize();
	gauge_frame_->__size(GAUGE_FRAME_SIZE);
	gauge_frame_->__point(Sprite::POINT_LEFT_MIDDLE);
	gauge_frame_->__texture_id(Texture::TEXTURE_ID_GAME_LIGHT_GAUGE_FRAME);
	gauge_frame_->SetParameter();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void ObjectLightGauge::Uninitialize(void)
{
	SafeRelease(gauge_);

	SafeRelease(gauge_frame_);

	SafeRelease(gauge_back_);
}

//=============================================================================
// update
//=============================================================================
void ObjectLightGauge::Update(void)
{
	gauge_->__size(D3DXVECTOR2(GAUGE_SIZE.x * rate_ / 100.0f,GAUGE_SIZE.y));
	gauge_->__right(rate_ / 100.0f);
	gauge_->SetParameter();
}

//=============================================================================
// draw
//=============================================================================
void ObjectLightGauge::Draw(void)
{
	gauge_back_->__position(position_);
	gauge_back_->Draw();

	gauge_->__position(position_ + GAUGE_POSITION);
	gauge_->Draw();

	gauge_frame_->__position(position_);
	gauge_frame_->Draw();
}

//---------------------------------- EOF --------------------------------------
