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
const D3DXVECTOR2 StageName::DEFAULT_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f, 85.0f);
const D3DXVECTOR2 StageName::DEFAULT_SIZE = D3DXVECTOR2(512.0f,64.0f);

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
void StageName::__set_name_texture(Stage::TYPE stage)
{
	switch(stage)
	{
	case Stage::TYPE_TUTORIAL:	//チュートリアル
	case Stage::TYPE_MAX:
	default:
		//ステージ名がよくわからないものはすべてテストテクスチャで表示
		name_->__texture_id(Texture::TEXTURE_ID_SELECT_STRING_TUTORIAL);
		name_->SetParameter();
		break;
	case Stage::TYPE_STAGE1:	//ステージ１
		name_->__texture_id(Texture::TEXTURE_ID_SELECT_STRING_STAGE_1);
		name_->SetParameter();
		break;
	case Stage::TYPE_STAGE2:	//ステージ１
		name_->__texture_id(Texture::TEXTURE_ID_SELECT_STRING_STAGE_2);
		name_->SetParameter();
		break;
	case Stage::TYPE_STAGE3:	//ステージ１
		name_->__texture_id(Texture::TEXTURE_ID_SELECT_STRING_STAGE_3);
		name_->SetParameter();
		break;
	case Stage::TYPE_STAGE4:	//ステージ１
		name_->__texture_id(Texture::TEXTURE_ID_SELECT_STRING_STAGE_4);
		name_->SetParameter();
		break;
	case Stage::TYPE_STAGE5:	//ステージ１
		name_->__texture_id(Texture::TEXTURE_ID_SELECT_STRING_STAGE_5);
		name_->SetParameter();
		break;
	case Stage::TYPE_STAGE6:	//ステージ１
		name_->__texture_id(Texture::TEXTURE_ID_SELECT_STRING_STAGE_6);
		name_->SetParameter();
		break;
	case Stage::TYPE_STAGE7:	//ステージ１
		name_->__texture_id(Texture::TEXTURE_ID_SELECT_STRING_STAGE_7);
		name_->SetParameter();
		break;
	case Stage::TYPE_STAGE8:	//ステージ１
		name_->__texture_id(Texture::TEXTURE_ID_SELECT_STRING_STAGE_8);
		name_->SetParameter();
		break;
	case Stage::TYPE_STAGE9:	//ステージ１
		name_->__texture_id(Texture::TEXTURE_ID_SELECT_STRING_STAGE_9);
		name_->SetParameter();
		break;
	case Stage::TYPE_STAGE10:	//ステージ１
		name_->__texture_id(Texture::TEXTURE_ID_SELECT_STRING_STAGE_10);
		name_->SetParameter();
		break;
	}
}

//---------------------------------- EOF --------------------------------------
