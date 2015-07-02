//*****************************************************************************
//
// gimmick �`���[�g���A���Ă�����
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
const u32 DEST_FRAME_COUNT = 15;						// �E�B���h�E�J�̎���
const D3DXVECTOR2 DEFAULT_POS_BACK (DEFAULT_SCREEN_WIDTH * 0.5f, DEFAULT_SCREEN_HEIGHT * 0.3f);		//�e�L�X�g�w�i�̈ʒu
const D3DXVECTOR2 DEFAULT_TXT_BACK (DEFAULT_SCREEN_WIDTH * 0.25f, DEFAULT_SCREEN_HEIGHT * 0.2f);	//�����̊J�n�ʒu
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
		txtbox_->Print("�ړ��L�[�ňړ�����j���X", TEXT_COLOR);
		break;
	case MASSAGE_TYPE_JUMP:
		txtbox_->Print("�W�����v�L�[�ŃW�����v����j���X", TEXT_COLOR);
		break;
	case MASSAGE_TYPE_LIGHT:
		txtbox_->Print("�����L�[�Ō�������j���X",TEXT_COLOR);
		break;
	case MASSAGE_TYPE_GIMMICK_GLAS:
		txtbox_->Print("�������łȂ��ƂƂ���Ȃ��j���X", TEXT_COLOR);
		break;
	case MASSAGE_TYPE_GIMMICK_MIRROR:
		txtbox_->Print("�������ĂԂ���Ɣ��˂���j���X", TEXT_COLOR);
		break;
	default:
		txtbox_->Print("�\�����镶�����Ȃ��j���X", TEXT_COLOR);
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
