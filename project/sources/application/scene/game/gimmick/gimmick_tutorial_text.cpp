//*****************************************************************************
//
// gimmick チュートリアルてきすと
//
// Author		: kitazawa taichi
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "gimmick_tutorial_text.h"
#include "render/text_box.h"
#include "system/directx9/font/font_texture.h"


//*****************************************************************************
// constant definition
//*****************************************************************************


//=============================================================================
// constructor
//=============================================================================
GimmickTutorialText::GimmickTutorialText(void)
	:Gimmick(TYPE_TUTORIAL_TEXT)
{
	data_._priority = 0;
	size_ = D3DXVECTOR2(128.0f,128.0f);
	draw_flag_ = true;
}

//=============================================================================
// destructor
//=============================================================================
GimmickTutorialText::~GimmickTutorialText(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool GimmickTutorialText::Initialize(void)
{
	txtbox_ = new TextBox(FontTexture::TYPE_MEIRYO,100);
	txtbox_->Initialize();

	switch(type_)
	{
	case MASSAGE_TYPE_MOVE:
		txtbox_->Print("移動キーで移動するニャス");
		break;
	case MASSAGE_TYPE_JUMP:
		txtbox_->Print("ジャンプキーでジャンプするニャス");
		break;
	case MASSAGE_TYPE_LIGHT:
		txtbox_->Print("光化キーで光化するニャス");
		break;
	case MASSAGE_TYPE_GIMMICK_GLAS:
		txtbox_->Print("光化中でないととおれないニャス");
		break;
	case MASSAGE_TYPE_GIMMICK_MIRROR:
		txtbox_->Print("光化してぶつかると反射するニャス");
		break;
	default:
		txtbox_->Print("表示する文字がないニャス");
	break;
	}
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void GimmickTutorialText::Uninitialize(void)
{
	SafeRelease(txtbox_);

}

//=============================================================================
// update
//=============================================================================
void GimmickTutorialText::Update(void)
{

}

//=============================================================================
// draw
//=============================================================================
void GimmickTutorialText::Draw(void)
{
	DEBUG_TOOL.__debug_display()->Print("%d\n",data_._priority);

	if(draw_flag_ == true)
	{
		txtbox_->Draw();
	}
}

//=============================================================================
// get pointer
//=============================================================================
void* GimmickTutorialText::GetPointer(void)
{
	return &data_;
}

//---------------------------------- EOF --------------------------------------
