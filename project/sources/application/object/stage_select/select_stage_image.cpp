//*****************************************************************************
//
// 選ばれるステージのまとまり
//	中心座標		player_->__point(
//
// Author		: kitazawa taichi
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "select_stage_image.h"
#include "render/sprite.h"
#include "system/system.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 StageImage::STAGE_SIZE = D3DXVECTOR2((f32)DEFAULT_SCREEN_WIDTH * 2.0f,(f32)DEFAULT_SCREEN_HEIGHT);
const D3DXVECTOR2 StageImage::DEFAULT_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f,DEFAULT_SCREEN_HEIGHT * 0.45f);
const D3DXVECTOR2 StageImage::DEFAULT_SIZE = D3DXVECTOR2(700.0f,450.0f);

//=============================================================================
// constructor
//=============================================================================
StageImage::StageImage(void)
	:size_(STAGE_SIZE)
	,offset_position_(0.0f,0.0f)
	,image_(nullptr)
{
}

//=============================================================================
// destructor
//=============================================================================
StageImage::~StageImage(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool StageImage::Initialize(void)
{
	image_ = new Sprite();

	if(!SafeInitialize(image_))
	{
		return false;
	}

	image_->__size(DEFAULT_SIZE);
	image_->__position(DEFAULT_POSITION);
	image_->__texture_id(Texture::TEXTURE_ID_SELECT_IMAGE_STAGE_1);
	image_->__index((u32)0);
	image_->__point(Sprite::POINT_CENTER);
	image_->SetParameter();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void StageImage::Uninitialize(void)
{
	SafeRelease(image_);
}

//=============================================================================
// update
//=============================================================================
void StageImage::Update(void)
{
	//位置の更新
	image_->__position(D3DXVECTOR2(DEFAULT_POSITION.x + offset_position_.x,DEFAULT_POSITION.y + offset_position_.y));
	image_->SetParameter();
}

//=============================================================================
// draw
//=============================================================================
void StageImage::Draw(void)
{
	image_->Draw();
}

//=============================================================================
//ステージイメージテクスチャの設定
//=============================================================================
void StageImage::__set_image_texture(Stage::TYPE stage)
{
	switch(stage)
	{
	case Stage::TYPE_TUTORIAL:	//チュートリアル
	case Stage::TYPE_MAX:
	default:
		//ステージイメージがよくわからないものの時はすべてテストテクスチャで表示
		image_->__texture_id(Texture::TEXTURE_ID_SELECT_IMAGE_STAGE_1);
		image_->SetParameter();

		break;
	}
}

//---------------------------------- EOF --------------------------------------
