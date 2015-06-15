//*****************************************************************************
//
// �X�e�[�W�Z���N�g��ʂ̈̂��z
//��������e�X�e�[�W�̂܂Ƃ܂�(stage_region)�����
//stage_region�͘g�A�X�e�[�W�C���[�W�A�X�e�[�W���A���R�[�h���܂Ƃ߂�����
//stage_region�̓X�e�[�W�̐��������
//
// Author		: kitazawa taichi
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _STAGE_SELECT_H_
#define _STAGE_SELECT_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "stage.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Sprite;
class StageRegion;
class SelectBg;
class SelectArrow;
class MessageWindow;
class Record;

//*****************************************************************************
// class definition
//*****************************************************************************
class StageSelect : public Stage
{
public:

	typedef struct REGIONS
	{
		StageRegion* region_;
		D3DXVECTOR2 position_;
		TYPE type_;
	};

	enum UPDATE_TYPE
	{
		UPDATE_TYPE_SELECT,		//�X�e�[�W�I�����Ă�Ƃ�
		UPDATE_TYPE_MASSAGE,	//�^�C�g���ɖ߂邩�����Ă�Ƃ�
		UPDATE_TYPE_YORN,		//�z���g�ɂ��̃X�e�[�W�ŗV�Ԃ������Ă�Ƃ�
		UPDATE_TYPE�QMAX
	};

	// constructor
	StageSelect(void);

	// destructor
	virtual ~StageSelect(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// create factory
	StageFactory* CreateFactory(void)const;

	// accessor

protected:

	void SelectUpdate();	// �X�e�[�W��I��ł�Ƃ��̍X�V
	void MassageUpdate();	// ���b�Z�[�W�E�B���h�E���o�Ă�Ƃ��̍X�V
	void YorNUpdate();		// �z���g�ɂ��̃X�e�[�W�ŗV�Ԃ������Ă�Ƃ��̍X�V

	REGIONS regions_[TYPE_MAX-1];

	SelectBg*	select_bg_;

	SelectArrow* select_arrow_;

	u32	current_stage_;

	Record* record_;

	// message_window
	MessageWindow* message_window_;
	bool massage_flag_;		//���b�Z�[�W�E�B���h�E�̏o�Ă邩�ǂ���
	UPDATE_TYPE update_type_;

};

#endif	// _STAGE_H_

//---------------------------------- EOF --------------------------------------
