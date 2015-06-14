//*****************************************************************************
//
// stage select bg
//
// Author		: taichi kitazawa
//
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "select_arrow_left.h"
#include "render/sprite.h"
#include "system/system.h"

const f32 DEFAULT_POS_X = 81.0f;				// デフォルトポジションX
const f32 DEFAULT_POS_Y = 400.0f;				// デフォルトポジションY
const u32 ARROW_FLASH_TIME = 10;				// 矢印の点滅速度

//=============================================================================
// constructor
//=============================================================================
ArrowLeft::ArrowLeft(void)
{
}

//=============================================================================
// destructor
//=============================================================================
ArrowLeft::~ArrowLeft(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool ArrowLeft::Initialize(void)
{
	time_ = 0;
	alpha_ = 255;

	arrow_left_ = new Sprite();
	arrow_left_->Initialize();
	arrow_left_->__size(D3DXVECTOR2((f32)81.0f,(f32)140.0f));
	arrow_left_->__position(D3DXVECTOR2(DEFAULT_POS_X,DEFAULT_POS_Y));
	arrow_left_->__texture_id(Texture::TEXTURE_ID_SELECT_ARROW_LEFT);
	arrow_left_->__point(Sprite::POINT_CENTER);
	arrow_left_->__color(D3DCOLOR_RGBA(255,255,255,alpha_));
	arrow_left_->SetParameter();
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void ArrowLeft::Uninitialize(void)
{
	SafeRelease(arrow_left_);
}

//=============================================================================
// update
//=============================================================================
void ArrowLeft::Update(void)
{
	time_++;

	if(time_==10)
	{
		if(alpha_==255)
		{
			alpha_ = 0;
		}
		else if(alpha_ == 0)
		{
			alpha_ = 255;
		}
		arrow_left_->__color(D3DCOLOR_RGBA(255,255,255,alpha_));
		arrow_left_->SetParameter();
		time_ = 0;
	}
}

//=============================================================================
// draw
//=============================================================================
void ArrowLeft::Draw(void)
{
	arrow_left_->Draw();
}

//---------------------------------- EOF --------------------------------------
