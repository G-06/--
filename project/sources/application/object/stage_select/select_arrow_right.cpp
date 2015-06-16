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
#include "select_arrow_right.h"
#include "render/sprite.h"
#include "system/system.h"

const u32 ARROW_FLASH_TIME = 10;				// 矢印の点滅速度
const D3DXVECTOR2 DEFAULT_POS((DEFAULT_SCREEN_WIDTH * 0.5f)+((850.0f*0.87f)*0.6f),340.0f);// デフォルトポジション
const D3DXVECTOR2 DEFAULT_SIZE(81.0f*0.95f,140.0f*0.92f);// デフォルトサイズ

//=============================================================================
// constructor
//=============================================================================
ArrowRight::ArrowRight(void)
{
}

//=============================================================================
// destructor
//=============================================================================
ArrowRight::~ArrowRight(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool ArrowRight::Initialize(void)
{
	time_ = 0;
	alpha_ = 255;

	arrow_right_ = new Sprite();
	arrow_right_->Initialize();
	arrow_right_->__size(DEFAULT_SIZE);
	arrow_right_->__position(DEFAULT_POS);
	arrow_right_->__texture_id(Texture::TEXTURE_ID_SELECT_ARROW_RIGHT);
	arrow_right_->__point(Sprite::POINT_CENTER);
	arrow_right_->__color(D3DCOLOR_RGBA(255,255,255,alpha_));
	arrow_right_->SetParameter();
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void ArrowRight::Uninitialize(void)
{
	SafeRelease(arrow_right_);
}

//=============================================================================
// update
//=============================================================================
void ArrowRight::Update(void)
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
		arrow_right_->__color(D3DCOLOR_RGBA(255,255,255,alpha_));
		arrow_right_->SetParameter();
		time_ = 0;
	}
}

//=============================================================================
// draw
//=============================================================================
void ArrowRight::Draw(void)
{
	arrow_right_->Draw();
}

//---------------------------------- EOF --------------------------------------
