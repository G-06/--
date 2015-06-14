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
#include "select_flame.h"
#include "render/sprite.h"
#include "system/system.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 SelectFrame::STAGE_SIZE = D3DXVECTOR2((f32)DEFAULT_SCREEN_WIDTH * 2.0f,(f32)DEFAULT_SCREEN_HEIGHT);
const D3DXVECTOR2 SelectFrame::DEFAULT_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f,DEFAULT_SCREEN_HEIGHT * 0.45f);
const D3DXVECTOR2 SelectFrame::DEFAULT_SIZE = D3DXVECTOR2(1000.0f,600.0f);

//=============================================================================
// constructor
//=============================================================================
SelectFrame::SelectFrame(void)
	:size_(STAGE_SIZE)
	,offset_position_(0.0f,0.0f)
{
}

//=============================================================================
// destructor
//=============================================================================
SelectFrame::~SelectFrame(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool SelectFrame::Initialize(void)
{
	frame_ = new Sprite();

	if(!SafeInitialize(frame_))
	{
		return false;
	}

	frame_->__size(DEFAULT_SIZE);
	frame_->__position(DEFAULT_POSITION);
	frame_->__texture_id(Texture::TEXTURE_ID_SELECT_STAGE_WINDOW);
	frame_->__index((u32)0);
	frame_->__point(Sprite::POINT_CENTER);
	frame_->SetParameter();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void SelectFrame::Uninitialize(void)
{
	SafeRelease(frame_);
}

//=============================================================================
// update
//=============================================================================
void SelectFrame::Update(void)
{

	frame_->__position(D3DXVECTOR2(DEFAULT_POSITION.x + offset_position_.x,DEFAULT_POSITION.y + offset_position_.y));
	frame_->SetParameter();
}

//=============================================================================
// draw
//=============================================================================
void SelectFrame::Draw(void)
{
	frame_->Draw();
}

//---------------------------------- EOF --------------------------------------
