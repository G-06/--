//*****************************************************************************
//
// player
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Sprite;

//*****************************************************************************
// class definition
//*****************************************************************************
class Player : public Basic
{
public:
	// constructor
	Player(void);

	// destructor
	virtual ~Player(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// Draw
	void Draw(void);

	// 座標の取得
	const D3DXVECTOR2& __position(void)const{ return position_; }

	// 前回座標の取得
	const D3DXVECTOR2& __old_position(void)const{ return old_position_; }

	// オフセット座標の設定
	void __offset_position(const D3DXVECTOR2& offset){ offset_position_ = offset; }

	// サイズ取得
	const D3DXVECTOR2& __size(void)const{ return size_; }

private:
	D3DXVECTOR2 position_;				// プレイヤー座標
	D3DXVECTOR2 old_position_;			// プレイヤーの前回座標
	D3DXVECTOR2 move_;					// プレイヤーの移動量
	D3DXVECTOR2 size_;					// プレイヤーサイズ
	D3DXVECTOR2 offset_position_;		// オフセット座標
	u32			acceleration_counter_;	// 加速カウンター
	u32			slowdown_counter_;		// 減速カウンター
	bool		is_left_;				// プレイヤーの向き
	bool		is_light_;				// 光化フラグ
	bool		is_fly_;				// 空中フラグ
	Sprite*		player_;				// プレイヤースプライト
	
};

#endif	// _PLAYER_H_

//---------------------------------- EOF --------------------------------------
