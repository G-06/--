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
#include "gimmick_massage.h"
#include "render/text_box.h"
#include "system/directx9/font/font_texture.h"
#include "application/object/message_window.h"
#include "application/object/tutorial_back.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const u32 DEST_FRAME_COUNT = 15;						// �E�B���h�E�J�̎���
const D3DXVECTOR2 DEFAULT_POS_BACK (DEFAULT_SCREEN_WIDTH * 0.5f, DEFAULT_SCREEN_HEIGHT * 0.27f);		//�e�L�X�g�w�i�̈ʒu
const D3DXVECTOR2 DEFAULT_TXT_BACK (DEFAULT_SCREEN_WIDTH * 0.24f, DEFAULT_SCREEN_HEIGHT * 0.16f);		//�����̊J�n�ʒu
const D3DXCOLOR TEXT_COLOR = D3DXCOLOR(1.0f, 1.0f, 0.3f, 1.0f);

//=============================================================================
// constructor
//=============================================================================
GimmickMassage::GimmickMassage(void)
	:Gimmick(TYPE_MASSAGE)
{
	size_ = D3DXVECTOR2(2300.0f,2600.0f);
}

//=============================================================================
// destructor
//=============================================================================
GimmickMassage::~GimmickMassage(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool GimmickMassage::Initialize(void)
{
	txtbox_ = new TextBox(FontTexture::TYPE_MEIRYO,50);
	txtbox_->Initialize();
	txtbox_->__show_speed(2);

	txtbox_->__position(DEFAULT_TXT_BACK);

	switch(type_)
	{
	case MASSAGE_TYPE_STAFF_TITLE:
//			txtbox_->Print("�u���[�j���X", TEXT_COLOR);
			txtbox_->Print("          BlueNyas\n\n", TEXT_COLOR);
			txtbox_->Print("     �`�[�� �E �R�l�R�o�R       ", TEXT_COLOR);
		break;
	case MASSAGE_TYPE_STAFF_MAKER:
			txtbox_->Print("\n     �������� �ЂƂ�����", TEXT_COLOR);
		break;
	case MASSAGE_TYPE_STAFF_LEADER:
//			txtbox_->Print("���[�_�[\n  �܂���  �܂���", TEXT_COLOR);
			txtbox_->Print("          ���[�_�[\n", TEXT_COLOR);
			txtbox_->Print("       �܂���  �܂���", TEXT_COLOR);
		break;
	case MASSAGE_TYPE_STAFF_DESIGNER:
//			txtbox_->Print("�f�U�C�i�[\n  �͂܂�  �݂�", TEXT_COLOR);
			txtbox_->Print("         �f�U�C�i�[\n", TEXT_COLOR);
			txtbox_->Print("        �͂܂�  �݂�", TEXT_COLOR);
		break;
	case MASSAGE_TYPE_STAFF_PLANER_1:
//			txtbox_->Print("�v�����i�[\n  �͂₵��  ������", TEXT_COLOR);
			txtbox_->Print("         �v�����i�[\n", TEXT_COLOR);
			txtbox_->Print("      �͂₵��  ������", TEXT_COLOR);
		break;
	case MASSAGE_TYPE_STAFF_PLANER_2:
//			txtbox_->Print("�v�����i�[\n  �܂���  ���傤����", TEXT_COLOR);
			txtbox_->Print("         �v�����i�[\n", TEXT_COLOR);
			txtbox_->Print("      �܂���  ���傤����", TEXT_COLOR);
		break;
	case MASSAGE_TYPE_STAFF_PROGRAMMER_1:
//			txtbox_->Print("���C���v���O���}�[\n  ���ԂƂ���  ����", TEXT_COLOR);
			txtbox_->Print("      ���C���v���O���}�[\n", TEXT_COLOR);
			txtbox_->Print("      ���ԂƂ���  ����", TEXT_COLOR);
		break;
	case MASSAGE_TYPE_STAFF_PROGRAMMER_2:
//			txtbox_->Print("�v���O���}�[\n  ���炢  ��傤���낤", TEXT_COLOR);
			txtbox_->Print("        �v���O���}�[\n", TEXT_COLOR);
			txtbox_->Print("      ���炢  ��傤���낤", TEXT_COLOR);
		break;
	case MASSAGE_TYPE_STAFF_PROGRAMMER_3:
//			txtbox_->Print("�v���O���}�[\n  ��������  ������", TEXT_COLOR);
			txtbox_->Print("        �v���O���}�[\n", TEXT_COLOR);
			txtbox_->Print("      ��������  ������", TEXT_COLOR);
		break;
	case MASSAGE_TYPE_STAFF_PROGRAMMER_4:
//			txtbox_->Print("�v���O���}�[\n  �����Ƃ�  �͂邫", TEXT_COLOR);
			txtbox_->Print("        �v���O���}�[\n", TEXT_COLOR);
			txtbox_->Print("       �����Ƃ�  �͂邫", TEXT_COLOR);
		break;
	case MASSAGE_TYPE_STAFF_SPECIAL_1:
//			txtbox_->Print("�T�E���h�f��\n  �|�P�b�g�T�E���h\n  ���炰�H��       ���ʉ����{\n", TEXT_COLOR);
			txtbox_->Print("        �T�E���h������\n", TEXT_COLOR);
			txtbox_->Print("  �|�P�b�g�T�E���h\n  ���炰�H��     ���ʉ����{\n", TEXT_COLOR);
		break;
	case MASSAGE_TYPE_STAFF_SPECIAL_2:
//			txtbox_->Print("�X�y�V�����T���N�X\n  ��܂���  �₷����", TEXT_COLOR);
			txtbox_->Print("     �X�y�V�����T���N�X\n", TEXT_COLOR);
			txtbox_->Print("     ��܂���  �₷����", TEXT_COLOR);
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
void GimmickMassage::Uninitialize(void)
{
	SafeRelease(txtbox_);
	SafeRelease(back_);

}

//=============================================================================
// update
//=============================================================================
void GimmickMassage::Update(void)
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
void GimmickMassage::Draw(void)
{
	back_->Draw();
	if(wait_ > DEST_FRAME_COUNT)
	{
		txtbox_->Draw();
	}
}

//=============================================================================
// get pointer
//=============================================================================
void* GimmickMassage::GetPointer(void)
{
	return &data_;
}

//---------------------------------- EOF --------------------------------------

/*
�u���[�j���X

���������@�ЂƂ�����

���[�_�[
�@�܂����@�܂���

�f�U�C�i�[
�@�͂܂��@�݂�

�v�����i�[
�@�͂₵���@������
�@�܂����@���傤����

���C���v���O���}�[
�@���ԂƂ���@����

�v���O���}�[
�@���炢�@��傤���낤
�@��������@������
�@�����Ƃ��@�͂邫

�X�y�V�����T���N�X
�@��܂����@�₷����
�@
�@������

�@
���@��@��

�@^�@�@^
( ���ց�)

*/
