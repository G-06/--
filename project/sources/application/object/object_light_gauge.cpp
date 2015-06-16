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
const D3DXVECTOR2 ObjectLightGauge::SIZE	= D3DXVECTOR2(128.0f,128.0f);
const u32 ObjectLightGauge::DIVISION_WIDTH	= 1;
const u32 ObjectLightGauge::DIVISION_HEIGHT	= 1;

//=============================================================================
// constructor
//=============================================================================
ObjectLightGauge::ObjectLightGauge(void)
	:gauge_(nullptr)
	,position_(0.0f,0.0f)
	,size_(0.0f,0.0f)
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
	size_ = SIZE;
	gauge_ = new Sprite();
	gauge_->Initialize();
	gauge_->__point(Sprite::POINT_LEFT_MIDDLE);
	gauge_->__division_width(DIVISION_WIDTH);
	gauge_->__division_height(DIVISION_HEIGHT);
	gauge_->__size(SIZE);
	gauge_->__texture_id(Texture::TEXTURE_ID_GAME_LIGHT_GAUGE);
	gauge_->SetParameter();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void ObjectLightGauge::Uninitialize(void)
{
	SafeRelease(gauge_);
}

//=============================================================================
// update
//=============================================================================
void ObjectLightGauge::Update(void)
{
	gauge_->__size(D3DXVECTOR2(size_.x * rate_ / 100.0f,size_.y));
	gauge_->SetParameter();
}

//=============================================================================
// draw
//=============================================================================
void ObjectLightGauge::Draw(void)
{
	gauge_->__position(position_);
	gauge_->Draw();
}

//---------------------------------- EOF --------------------------------------
