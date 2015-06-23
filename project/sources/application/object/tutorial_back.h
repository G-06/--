//*****************************************************************************
//
// チュートリアル拝啓
//
// Author	: kitazawa taichi
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _TUTORIAL_BACK_H_
#define _TUTORIAL_BACK_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"
#include "system/directx9/texture/texture.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class MessageSpriteSmooth;

//*****************************************************************************
// class definition
//*****************************************************************************
class TutorialBack : public Basic
{
public:
	// constructor
	TutorialBack(void);

	// destructor
	virtual ~TutorialBack(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// メッセージの種類
	enum MESSAGE{
		MESSAGE_YES = 0,
		MESSAGE_NO,
		MESSAGE_MAX
	};

	// show close
	// 良い感じに開閉
	void Show(void);
	void Close(void);

	const bool& __is_show(void) {return is_show_;}
	void __dest_frame_count(const u32& frame){dest_frame_count_ = frame;}
	const bool& __is_move(void) {return is_move_;}

	void __window_position(const D3DXVECTOR2& position){window_position_ = position;}
	void __window_size(const D3DXVECTOR2& size){window_size_ = size;}

private:

	static const D3DXVECTOR2 DEFAULT_POSITION;
	static const D3DXVECTOR2 DEFAULT_SIZE;
	static const u32 SELECT_MAX = MESSAGE_MAX;

	// 切替え用
	void _ChangeSelect(const s32& now, const s32& old);

	MessageSpriteSmooth* window_;

	// 規定位置
	D3DXVECTOR2 window_position_;

	// 移動するまでのカウント
	u32 dest_frame_count_;


	// 開いている？
	bool is_show_;

	// 動いてる？
	bool is_move_;

	// size
	D3DXVECTOR2 window_size_;
};

#endif	// _MESSAGE_WINDOW_H_

//---------------------------------- EOF --------------------------------------
