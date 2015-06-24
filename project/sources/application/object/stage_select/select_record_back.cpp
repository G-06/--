//*****************************************************************************
//
// ステージ名のテクスチャ
//	中心座標		player_->__point(
//
// Author		: kitazawa taichi
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "select_record_back.h"
#include "render/sprite.h"
#include "system/system.h"


//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 RecordBack::STAGE_SIZE = D3DXVECTOR2((f32)DEFAULT_SCREEN_WIDTH * 2.0f,(f32)DEFAULT_SCREEN_HEIGHT);
const D3DXVECTOR2 RecordBack::DEFAULT_SIZE = D3DXVECTOR2(330.0f,75.0f);
const D3DXVECTOR2 RecordBack::DEFAULT_POSITION = D3DXVECTOR2(800.f,500.f);

//=============================================================================
// constructor
//=============================================================================
RecordBack::RecordBack(void)
	:size_(STAGE_SIZE)
	,offset_position_(0.0f,0.0f)
	,record_back_(nullptr)
{
}

//=============================================================================
// destructor
//=============================================================================
RecordBack::~RecordBack(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool RecordBack::Initialize(void)
{
	record_back_ = new Sprite();

	if(!SafeInitialize(record_back_))
	{
		return false;
	}

	position_ = DEFAULT_POSITION;

	record_back_->__size(DEFAULT_SIZE);
	record_back_->__position(position_);
	record_back_->__texture_id(Texture::TEXTURE_ID_SELECT_TIME_FRAME);
	record_back_->__index((u32)0);
	record_back_->__point(Sprite::POINT_CENTER);
	record_back_->SetParameter();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void RecordBack::Uninitialize(void)
{
	SafeRelease(record_back_);
}

//=============================================================================
// update
//=============================================================================
void RecordBack::Update(void)
{
	record_back_->__position(D3DXVECTOR2(position_.x + offset_position_.x,position_.y + offset_position_.y));
	record_back_->SetParameter();
}

//=============================================================================
// draw
//=============================================================================
void RecordBack::Draw(void)
{
	record_back_->Draw();
}

//---------------------------------- EOF --------------------------------------
