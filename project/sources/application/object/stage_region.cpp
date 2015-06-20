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
const f32 MOVE_SPEED = 60.f;				// まとまりの移動速度 フレーム数で指定
const f32 MOVE_FREAM = 960.0f/MOVE_SPEED;


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
	stage_name_->__set_name_texture(Stage::TYPE_MAX);

	//ステージSSテクスチャ
	stage_image_ = new StageImage();
	if(!SafeInitialize(stage_image_))
	{
		return false;
	}
	stage_image_->__set_image_texture(Stage::TYPE_MAX);

	//レコード表示
	record_ = new SelectRecord();
	if(!SafeInitialize(record_))
	{
		return false;
	}

	move_falg_ = false;

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
	move_falg_ = false;

	if(region_pos_.x>region_distpos_.x)
	{
		region_pos_.x -= MOVE_FREAM;
		move_falg_ = true;
	}
	if(region_pos_.x<region_distpos_.x)
	{
		region_pos_.x += MOVE_FREAM;
		move_falg_ = true;
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
	stage_image_->Draw();
	select_frame_->Draw();
	stage_name_->Draw();
	if(type_ != Stage::TYPE_TUTORIAL)
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
void StageRegion::__set_stage_id(Stage::TYPE stage)
{
	stage_name_->__set_name_texture(stage);
	stage_image_->__set_image_texture(stage);
	type_= stage;
}

void StageRegion::__set_time(u32 time)
{
	record_->__set_time(time);
}

//---------------------------------- EOF --------------------------------------
