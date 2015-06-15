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

	// create factory
	StageFactory* CreateFactory(void)const;

	// accessor

protected:

	void SelectUpdate();	// ステージを選んでるときの更新
	void MassageUpdate();	// メッセージウィンドウが出てるときの更新
	void YorNUpdate();		// ホントにこのステージで遊ぶか聞いてるときの更新

	REGIONS regions_[TYPE_MAX-1];

	SelectBg*	select_bg_;

	SelectArrow* select_arrow_;

	u32	current_stage_;

	Record* record_;

	// message_window
	MessageWindow* message_window_;
	bool massage_flag_;		//メッセージウィンドウの出てるかどうか
	UPDATE_TYPE update_type_;

};

#endif	// _STAGE_H_

//---------------------------------- EOF --------------------------------------
