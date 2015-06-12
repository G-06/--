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
#include "basic/basic.h"


//*****************************************************************************
// forward declaration
//*****************************************************************************
class Sprite;
class StageRegion;
class SelectBg;
class SelectArrow;

enum STAGE_ID
{
	STAGE_ID_SELECT = -1,
	STAGE_ID_0,		//�`���[�g���A��
	STAGE_ID_1,		//�X�e�[�W1
	STAGE_ID_2,		//�X�e�[�W2

	STAGE_ID_MAX
};

//*****************************************************************************
// class definition
//*****************************************************************************
class StageSelect : public Basic
{
public:
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

	// accessor
	//void __size(const D3DXVECTOR2& size) { size_ = size; }
	//const D3DXVECTOR2& __size(void)const { return size_; }
	//void __offset_position(const D3DXVECTOR2& offset_position) { offset_position_ = offset_position; }

protected:

	StageRegion* regions_[STAGE_ID_MAX];

	SelectBg*	select_bg_;

	SelectArrow* select_arrow_;

	u32	current_stage_;
};

#endif	// _STAGE_H_

//---------------------------------- EOF --------------------------------------
