//*****************************************************************************
//
// record
//
// Author	: masato masuda
//
//	���R�[�h�i�X�e�[�W���̃n�C�X�R�A�j�̕ێ�
//	���R�[�h�̃Z�[�u�����[�h
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _RECORD_H_
#define _RECORD_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"

//*****************************************************************************
// class definition
//*****************************************************************************
class Record : public Basic
{
public:
	// constructor
	Record(void);

	// destructor
	virtual ~Record(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);


	// �擾
	s32 __record(const u32 stage_num);

	// �ݒ�
	bool __record(const u32 stage_num, const u32 record);

	// loadFile
	bool LoadFile(const s8* file_name);

	// saveFile
	bool SaveFile(const s8* file_name);

	// saveFile(���R�[�h�N���A�j
	bool SaveFileClear(const s8* file_name, const u32 stage_num);

private:

	// �X�e�[�W��
	u32		stage_num_;

	// �X�e�[�W���̃n�C�X�R�A
	u32*	record_;
};


#endif	// _RECORD_H_


//---------------------------------- EOF --------------------------------------
