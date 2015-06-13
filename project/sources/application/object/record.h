//*****************************************************************************
//
// record
//
// Author	: masato masuda
//
//	レコード（ステージ毎のハイスコア）の保持
//	レコードのセーブ＆ロード
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


	// 取得
	s32 __record(const u32 stage_num);

	// 設定
	bool __record(const u32 stage_num, const u32 record);

	// loadFile
	bool LoadFile(const s8* file_name);

	// saveFile
	bool SaveFile(const s8* file_name);

	// saveFile(レコードクリア）
	bool SaveFileClear(const s8* file_name, const u32 stage_num);

private:

	// ステージ数
	u32		stage_num_;

	// ステージ毎のハイスコア
	u32*	record_;
};


#endif	// _RECORD_H_


//---------------------------------- EOF --------------------------------------
