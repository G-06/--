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

const D3DXVECTOR2 DEFAULT_SIZE(81.0f*0.95f,140.0f*0.92f);	// デフォルトサイズ
const u32 ARROW_FLASH_TIME = 10;							// 矢印の点滅速度
const D3DXVECTOR2 DEFAULT_POS((DEFAULT_SCREEN_WIDTH * 0.5f)-((850.0f*0.87f)*0.6f),340.0f);				// デフォルトポジション

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
	arrow_left_->__size(DEFAULT_SIZE);
	arrow_left_->__position(DEFAULT_POS);
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
