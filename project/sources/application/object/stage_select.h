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
class MessageWindow;


enum STAGE_ID
{
	STAGE_ID_END = -2,
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
	enum UPDATE_TYPE
	{
		UPDATE_TYPE_SELECT,		//ステージ選択してるとき
		UPDATE_TYPE_MASSAGE,	//タイトルに戻るか聞いてるとき
		UPDATE_TYPE_YORN,		//ホントにこのステージで遊ぶか聞いてるとき
		UPDATE_TYPE＿MAX
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

	// accessor
	//void __size(const D3DXVECTOR2& size) { size_ = size; }
	//const D3DXVECTOR2& __size(void)const { return size_; }
	//void __offset_position(const D3DXVECTOR2& offset_position) { offset_position_ = offset_position; }

protected:

	void SelectUpdate();	// ステージを選んでるときの更新
	void MassageUpdate();	// メッセージウィンドウが出てるときの更新
	void YorNUpdate();		// ホントにこのステージで遊ぶか聞いてるときの更新

	StageRegion* regions_[STAGE_ID_MAX];

	SelectBg*	select_bg_;

	SelectArrow* select_arrow_;

	u32	current_stage_;

	// message_window
	MessageWindow* message_window_;
	bool massage_flag_;		//メッセージウィンドウの出てるかどうか
	UPDATE_TYPE update_type_;


};

#endif	// _STAGE_H_

//---------------------------------- EOF --------------------------------------
