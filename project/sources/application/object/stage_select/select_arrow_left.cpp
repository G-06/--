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
	arrow_left_->__position(D3DXVECTOR2(81.0f,400.0f));
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

void ArrowLeft::__Alpha_On(void)
{
	alpha_ = 255;
	arrow_left_->__color(D3DCOLOR_RGBA(255,255,255,alpha_));
	arrow_left_->SetParameter();
}
void ArrowLeft::__Alpha_Off(void)
{
	alpha_ = 0;
	arrow_left_->__color(D3DCOLOR_RGBA(255,255,255,alpha_));
	arrow_left_->SetParameter();
}


//---------------------------------- EOF --------------------------------------
