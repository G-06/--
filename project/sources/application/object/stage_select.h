//*****************************************************************************
//
// ステージセレクト画面の偉い奴
//ここから各ステージのまとまり(stage_region)を作る
//stage_regionは枠、ステージイメージ、ステージ名、レコードをまとめたもの
//stage_regionはステージの数だけ作る
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
	STAGE_ID_0,		//チュートリアル
	STAGE_ID_1,		//ステージ1
	STAGE_ID_2,		//ステージ2

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
