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
#include "common/animation/animation.h"

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
	enum COLLISION_MODE
	{
		COLLISION_DOWN = 0,
		COLLISION_RIGHT,
		COLLISION_LEFT,
		COLLISION_MAX
	};

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

	void HitStage(const D3DXVECTOR2& position,bool is_floor = false);

	// ステージ衝突後処理
	void Stagecollision(u32 mode, D3DXVECTOR2 stage_size);

	// 座標の取得
	const D3DXVECTOR2& __position(void)const{ return position_; }

	void __position(const D3DXVECTOR2& position){ position_ = position; }

	// 前回座標の取得
	const D3DXVECTOR2& __old_position(void)const{ return old_position_; }

	// オフセット座標の設定
	void __offset_position(const D3DXVECTOR2& offset){ offset_position_ = offset; }

	// サイズ取得
	const D3DXVECTOR2& __size(void)const{ return size_; }

private:
	void LightMode(bool is_light, bool is_right);

	enum ANIMATION_TYPE
	{
		ANIMATION_TYPE_WAIT = 0,
		ANIMATION_TYPE_RUN,
		ANIMATION_TYPE_LIGHT,
		ANIMATION_TYPE_MAX
	};
	static const Animation::DATA ANIMATION_DATA[];
	static const u32 ANIMATION_RUN_START = (0);
	static const u32 ANIMATION_WAIT_START = (6);
	static const u32 ANIMATION_LIGHT_START = (7);
	static const f32 LIGHT_SPEED;
	static const f32 MAX_SPEED;
	static const f32 JUMP_SPEED;

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
	bool		is_enable_light_;
	Sprite*		player_;				// プレイヤースプライト
	Animation*	animation_;
	ANIMATION_TYPE animation_type_;
};

#endif	// _PLAYER_H_

//---------------------------------- EOF --------------------------------------
