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
#include "select_number.h"
#include "render/sprite.h"
#include "system/system.h"

const D3DXVECTOR2 DEFAULT_SIZE(50.0f*0.6f,100.0f*0.6f);	// デフォルトサイズ
const D3DXVECTOR2 DEFAULT_POS(0.f,0.f);					// デフォルトポジション

//=============================================================================
// constructor
//=============================================================================
Number::Number(void)
{
}

//=============================================================================
// destructor
//=============================================================================
Number::~Number(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool Number::Initialize(void)
{
	index_ = 0;

	position_ = D3DXVECTOR2(0.0f,0.0f);
	number_ = new Sprite();
	number_->Initialize();
	number_->__size(DEFAULT_SIZE);
	number_->__position(position_);
	number_->__texture_id(Texture::TEXTURE_ID_GENERAL_NUMBER);
	number_->__division_height(1);
	number_->__division_width(13);
	number_->__index(index_);

	number_->__point(Sprite::POINT_CENTER);
	number_->__color(D3DCOLOR_RGBA(255,255,255,255));
	number_->SetParameter();
	offset_position_ = D3DXVECTOR2(0.0f,0.0f);

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void Number::Uninitialize(void)
{
	SafeRelease(number_);
}

//=============================================================================
// update
//=============================================================================
void Number::Update(void)
{
	number_->__position(D3DXVECTOR2((position_.x + offset_position_.x),(position_.y + offset_position_.y)));
	number_->__index(index_);
	number_->SetParameter();
}

//=============================================================================
// draw
//=============================================================================
void Number::Draw(void)
{
	number_->Draw();
}


//---------------------------------- EOF --------------------------------------
