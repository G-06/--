//*****************************************************************************
//
// �I�΂��X�e�[�W�̂܂Ƃ܂�
//
// Author		: kitazawa taichi
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _STAGE_REGION_H_
#define _STAGE_REGION_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"
#include "stage_select.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Sprite;
class SelectFrame;
class StageName;
class StageImage;
class SelectRecord;

//*****************************************************************************
// class definition
//*****************************************************************************
class StageRegion : public Basic
{
public:
	// constructor
	StageRegion(void);

	// destructor
	virtual ~StageRegion(void);

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
	const D3DXVECTOR2& __size(void)const { return size_; }
	void __offset_position(const D3DXVECTOR2& offset_position) { offset_position_ = offset_position; }

	//�w��ʒu�Ɉړ�
	void __set_region_distpos(D3DXVECTOR2 offset_pos);
	//�X�e�[�WID�ݒ�
	void __set_stage_id(STAGE_ID stage);
	void __set_time(u32 time);

protected:
	static const D3DXVECTOR2 STAGE_SIZE;
	D3DXVECTOR2 size_;
	D3DXVECTOR2 offset_position_;

	D3DXVECTOR2 region_pos_;		//�܂Ƃ܂�S�̂̈ʒu
	D3DXVECTOR2 region_distpos_;		//�܂Ƃ܂�S�̂̐��������ʒu


	SelectFrame* select_frame_;		//�g
	StageName* stage_name_;			//���O
	StageImage* stage_image_;		//�C���[�W�摜
	SelectRecord* record_;


};

#endif	// _STAGE_H_

//---------------------------------- EOF --------------------------------------
