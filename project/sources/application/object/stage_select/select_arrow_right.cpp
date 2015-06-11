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
	arrow_right_->__size(D3DXVECTOR2((f32)81.0f,(f32)140.0f));
	arrow_right_->__position(D3DXVECTOR2(1180.0f,400.0f));
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


void ArrowRight::__Alpha_On(void)
{
	alpha_ = 255;
	arrow_right_->__color(D3DCOLOR_RGBA(255,255,255,alpha_));
	arrow_right_->SetParameter();
}
void ArrowRight::__Alpha_Off(void)
{
	alpha_ = 0;
	arrow_right_->__color(D3DCOLOR_RGBA(255,255,255,alpha_));
	arrow_right_->SetParameter();
}

//---------------------------------- EOF --------------------------------------
