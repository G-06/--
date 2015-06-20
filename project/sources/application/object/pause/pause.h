//*****************************************************************************
//
// pause
//
// Author	: masato masuda
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _PAUSE_H_
#define _PAUSE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"
#include "system/directx9/texture/texture.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class SpriteSmooth;

//*****************************************************************************
// class definition
//*****************************************************************************
class Pause : public Basic
{
public:
	// constructor
	Pause(void);

	// destructor
	virtual ~Pause(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// 選択肢の種類
	enum SELECT_TYPE {
		SELECT_TYPE_GAME_BACK = 0,
		SELECT_TYPE_TITLE_BACK,
		SELECT_TYPE_STAGESELECT_BACK,
		SELECT_TYPE_OPTION,
		SELECT_TYPE_MAX
	};

	// show close
	// 良い感じに開閉
	void Show(void);
	void Close(void);

	const bool& __is_show(void) {return is_show_;}
	void __dest_frame_count(const u32& frame){dest_frame_count_ = frame;}
	const bool& __is_move(void) {return is_move_;}

	// 選択中の取得
	const s32& __is_select(void){return is_select_;}
	void __is_select(const s32& select){is_select_ = select;}

	// 大きさ
	void __title_size(const D3DXVECTOR2& size){title_size_ = size;}
	void __select_size(const D3DXVECTOR2& size){select_size_ = size;}
	void __title_texture_id_(const Texture::TEXTURE_ID& texture_id);

	// 選択肢の移動
	void SelectUp(void);
	void SelectDown(void);

private:

	static const D3DXVECTOR2 DEFAULT_POSITION;
	static const D3DXVECTOR2 DEFAULT_SIZE;
	static const u32 SELECT_MAX = SELECT_TYPE_MAX;

	// 切替え用
	void _ChangeSelect(const s32& now, const s32& old);

	SpriteSmooth* bg_;
	SpriteSmooth* title_;
	SpriteSmooth* select_[SELECT_MAX];
	SpriteSmooth* frame_[SELECT_MAX];

	// 規定位置
//	D3DXVECTOR2 window_position_;

	// 移動するまでのカウント
	u32 dest_frame_count_;

	// 選択肢
	s32 is_select_;

	// 開いている？
	bool is_show_;

	// 動いてる？
	bool is_move_;

	// size
	D3DXVECTOR2 title_size_;
	D3DXVECTOR2 select_size_;
};

#endif	// _PAUSE_H_

//---------------------------------- EOF --------------------------------------
