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
#include "select_stage_name.h"
#include "render/sprite.h"
#include "system/system.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 StageName::STAGE_SIZE = D3DXVECTOR2((f32)DEFAULT_SCREEN_WIDTH * 2.0f,(f32)DEFAULT_SCREEN_HEIGHT);
const D3DXVECTOR2 StageName::DEFAULT_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f,100);
const D3DXVECTOR2 StageName::DEFAULT_SIZE = D3DXVECTOR2(200.0f,100.0f);

//=============================================================================
// constructor
//=============================================================================
StageName::StageName(void)
	:size_(STAGE_SIZE)
	,offset_position_(0.0f,0.0f)
	,name_(nullptr)
{
}

//=============================================================================
// destructor
//=============================================================================
StageName::~StageName(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool StageName::Initialize(void)
{
	name_ = new Sprite();

	if(!SafeInitialize(name_))
	{
		return false;
	}

	name_->__size(DEFAULT_SIZE);
	name_->__position(DEFAULT_POSITION);
	name_->__texture_id(Texture::TEXTURE_ID_SELECT_STRING_STAGE_1);
	name_->__index((u32)0);
	name_->__point(Sprite::POINT_CENTER);
	name_->SetParameter();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void StageName::Uninitialize(void)
{
	SafeRelease(name_);
}

//=============================================================================
// update
//=============================================================================
void StageName::Update(void)
{
	name_->__position(D3DXVECTOR2(DEFAULT_POSITION.x + offset_position_.x,DEFAULT_POSITION.y + offset_position_.y));
	name_->SetParameter();
}

//=============================================================================
// draw
//=============================================================================
void StageName::Draw(void)
{
	name_->Draw();
}

//=============================================================================
//ステージ名テクスチャの設定
//=============================================================================
void StageName::__set_name_texture(u32 stage)
{
	switch(stage)
	{
	//case STAGE_ID_SELECT:
	//case STAGE_ID_MAX:
	default:
		//ステージ名がよくわからないものはすべてテストテクスチャで表示
		name_->__texture_id(Texture::TEXTURE_ID_SELECT_STRING_STAGE_1);
		name_->SetParameter();
		break;

//	case STAGE_ID_0:
//		name_->__texture_id(Texture::TEXTURE_ID_SELECT_STRING_STAGE_1);
//		name_->SetParameter();
//		break;
//	case STAGE_ID_1:
//		name_->__texture_id(Texture::TEXTURE_ID_SELECT_STRING_STAGE_2);
//		name_->SetParameter();
//		break;
	}
}

//---------------------------------- EOF --------------------------------------
