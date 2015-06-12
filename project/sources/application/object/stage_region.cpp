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
#include "stage_region.h"
#include "render/sprite.h"
#include "system/system.h"

#include "stage_select/select_flame.h"
#include "stage_select/select_stage_name.h"
#include "stage_select/select_stage_image.h"
#include "stage_select/select_record.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 StageRegion::STAGE_SIZE = D3DXVECTOR2((f32)DEFAULT_SCREEN_WIDTH * 2.0f,(f32)DEFAULT_SCREEN_HEIGHT);


//=============================================================================
// constructor
//=============================================================================
StageRegion::StageRegion(void)
		:size_(STAGE_SIZE)
		,offset_position_(0.0f,0.0f)
		,select_frame_(nullptr)
		,stage_name_(nullptr)
		,stage_image_(nullptr)

{
}

//=============================================================================
// destructor
//=============================================================================
StageRegion::~StageRegion(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool StageRegion::Initialize(void)
{
	region_pos_ = D3DXVECTOR2(0.0f,0.0f);
	region_distpos_ = D3DXVECTOR2(0.0f,0.0f);

	//ステージ枠
	select_frame_ = new SelectFrame();
	if(!SafeInitialize(select_frame_))
	{
		return false;
	}

	//ステージ名テクスチャ
	stage_name_ = new StageName();
	if(!SafeInitialize(stage_name_))
	{
		return false;
	}
	stage_name_->__set_name_texture(STAGE_ID_MAX);

	//ステージSSテクスチャ
	stage_image_ = new StageImage();
	if(!SafeInitialize(stage_image_))
	{
		return false;
	}
	stage_image_->__set_image_texture(STAGE_ID_MAX);

	//レコード受け取り？

	//レコード表示
	record_ = new SelectRecord();
	if(!SafeInitialize(record_))
	{
		return false;
	}

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void StageRegion::Uninitialize(void)
{
	SafeRelease(select_frame_);
	SafeRelease(stage_name_);
	SafeRelease(stage_image_);
	SafeRelease(record_);

}

//=============================================================================
// update
//=============================================================================
void StageRegion::Update(void)
{
	if(region_pos_.x>region_distpos_.x)
	{
		region_pos_.x -= 100.0f;
	}
	if(region_pos_.x<region_distpos_.x)
	{
		region_pos_.x += 100.0f;
	}

	select_frame_->__offset_position(region_pos_);
	stage_name_->__offset_position(region_pos_);
	stage_image_->__offset_position(region_pos_);
	record_->__offset_position(region_pos_);



	select_frame_->Update();
	stage_name_->Update();
	stage_image_->Update();
	record_->Update();
}

//=============================================================================
// draw
//=============================================================================
void StageRegion::Draw(void)
{
	select_frame_->Draw();
	stage_name_->Draw();
	stage_image_->Draw();
	record_ ->Draw();
}

//=============================================================================
//指定位置に移動
//=============================================================================
void StageRegion::__set_region_distpos(D3DXVECTOR2 offset_pos)
{
	region_distpos_ += offset_pos;
}

//=============================================================================
//ステージID設定
//=============================================================================
void StageRegion::__set_stage_id(STAGE_ID stage)
{
	stage_name_->__set_name_texture(stage);
	stage_image_->__set_image_texture(stage);
}

void StageRegion::__set_time(u32 time)
{
	record_->__set_time(time);
}


//---------------------------------- EOF --------------------------------------
