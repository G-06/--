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
#include "application/object/message_window.h"
#include "application/object/tutorial_back.h"


//*****************************************************************************
// constant definition
//*****************************************************************************
const u32 DEST_FRAME_COUNT = 15;						// ウィンドウ開閉の時間
const D3DXVECTOR2 DEFAULT_POS_BACK (DEFAULT_SCREEN_WIDTH * 0.5f, DEFAULT_SCREEN_HEIGHT * 0.3f);		//テキスト背景の位置
const D3DXVECTOR2 DEFAULT_TXT_BACK (DEFAULT_SCREEN_WIDTH * 0.25f, DEFAULT_SCREEN_HEIGHT * 0.2f);	//文字の開始位置
const D3DXCOLOR TEXT_COLOR = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

//=============================================================================
// constructor
//=============================================================================
GimmickTutorialText::GimmickTutorialText(void)
	:Gimmick(TYPE_TUTORIAL_TEXT)
{
	data_._priority = 0;
	size_ = D3DXVECTOR2(256.0f,128.0f);
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
	txtbox_ = new TextBox(FontTexture::TYPE_MEIRYO,50);
	txtbox_->Initialize();
	txtbox_->__show_speed(2);

	txtbox_->__position(DEFAULT_TXT_BACK);

	switch(type_)
	{
	case MASSAGE_TYPE_MOVE:
		txtbox_->Print("移動キーで移動するニャス", TEXT_COLOR);
		break;
	case MASSAGE_TYPE_JUMP:
		txtbox_->Print("ジャンプキーでジャンプするニャス", TEXT_COLOR);
		break;
	case MASSAGE_TYPE_LIGHT:
		txtbox_->Print("光化キーで光化するニャス",TEXT_COLOR);
		break;
	case MASSAGE_TYPE_GIMMICK_GLAS:
		txtbox_->Print("光化中でないととおれないニャス", TEXT_COLOR);
		break;
	case MASSAGE_TYPE_GIMMICK_MIRROR:
		txtbox_->Print("光化してぶつかると反射するニャス", TEXT_COLOR);
		break;
	default:
		txtbox_->Print("表示する文字がないニャス", TEXT_COLOR);
	break;
	}

	wait_ = 0;

	// message_window
	back_ = new TutorialBack();
	back_->Initialize();
	back_->__dest_frame_count(DEST_FRAME_COUNT);
	back_->__window_position(DEFAULT_POS_BACK);
	back_flag_ = false;



	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void GimmickTutorialText::Uninitialize(void)
{
	SafeRelease(txtbox_);
	SafeRelease(back_);

}

//=============================================================================
// update
//=============================================================================
void GimmickTutorialText::Update(void)
{
	if(data_._is_hit == true)
	{
		if(back_flag_ == false)
		{
			back_->Show();
			back_flag_ = true;
		}
		if(wait_== DEST_FRAME_COUNT)
		{
			txtbox_->Restart();
		}
		wait_++;
	}
	else if(data_._is_hit == false)
	{
		if(back_flag_ == true)
		{
			back_->Close();
			wait_ = 0;
			back_flag_ = false;
		}
	}

	back_->Update();
	data_._is_hit=false;
}


//=============================================================================
// draw
//=============================================================================
void GimmickTutorialText::Draw(void)
{
	back_->Draw();
	DEBUG_TOOL.__debug_display()->Print("%d\n",data_._priority);
	if(wait_ > DEST_FRAME_COUNT)
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
