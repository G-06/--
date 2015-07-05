//*****************************************************************************
//
// message_window
//
// Author	: masato masuda
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _MESSAGE_WINDOW_H_
#define _MESSAGE_WINDOW_H_

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
class MessageWindow : public Basic
{
public:
	// constructor
	MessageWindow(void);

	// destructor
	virtual ~MessageWindow(void);

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
	const s32& __is_select(void){return is_select_;}

	// 選択中の取得
	void __is_select(const s32& select){is_select_ = select;}

	void __window_position(const D3DXVECTOR2& position){window_position_ = position;}
	void __window_size(const D3DXVECTOR2& size){window_size_ = size;}
	void __title_size(const D3DXVECTOR2& size){title_size_ = size;}
	void __select_size(const D3DXVECTOR2& size){select_size_ = size;}
	void __title_texture_id_(const Texture::TEXTURE_ID& texture_id);
	void __select_frame_texture_id_(const s32 select_number, const Texture::TEXTURE_ID& texture_id);

	// 選択肢の移動
	void SelectUp(void);
	void SelectDown(void);

private:

	static const D3DXVECTOR2 DEFAULT_POSITION;
	static const D3DXVECTOR2 DEFAULT_SIZE;
	static const u32 SELECT_MAX = MESSAGE_MAX;

	// 切替え用
	void _ChangeSelect(const s32& now, const s32& old);

	MessageSpriteSmooth* window_;
	MessageSpriteSmooth* title_;
	MessageSpriteSmooth* select_[SELECT_MAX];
	MessageSpriteSmooth* frame_[SELECT_MAX];

	// 規定位置
	D3DXVECTOR2 window_position_;

	// 移動するまでのカウント
	u32 dest_frame_count_;

	// 選択肢
	s32 is_select_;

	// 開いている？
	bool is_show_;

	// 動いてる？
	bool is_move_;

	// size
	D3DXVECTOR2 window_size_;
	D3DXVECTOR2 title_size_;
	D3DXVECTOR2 select_size_;
};

#endif	// _MESSAGE_WINDOW_H_

//---------------------------------- EOF --------------------------------------
