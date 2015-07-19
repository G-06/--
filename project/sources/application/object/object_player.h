//*****************************************************************************
//
// object player
//
// Author		: Ryotaro Arai
//				: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _OBJECT_PLAYER_H_
#define _OBJECT_PLAYER_H_

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
class ObjectPlayer : public Basic
{
public:
	enum ANIMATION_TYPE
	{
		ANIMATION_TYPE_WAIT = 0,
		ANIMATION_TYPE_RUN,
		ANIMATION_TYPE_JUMP,
		ANIMATION_TYPE_FALL,
		ANIMATION_TYPE_LIGHT_START,
		ANIMATION_TYPE_LIGHT_END,
		ANIMATION_TYPE_LIGHT,
		ANIMATION_TYPE_DAMAGE,
		ANIMATION_TYPE_GAME_START,
		ANIMATION_TYPE_GAME_END,
		ANIMATION_TYPE_DEAD,
		ANIMATION_TYPE_JOY,
		ANIMATION_TYPE_MAX
	};

	// constructor
	ObjectPlayer(void);

	// destructor
	virtual ~ObjectPlayer(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// start animation
	void StartAnimation(ANIMATION_TYPE animation_type);

	// set size
	void SetSize(const D3DXVECTOR2& size);

	// 座標の取得
	const D3DXVECTOR2& __position(void)const{ return position_; }
	void __position(const D3DXVECTOR2& position){ position_ = position; }
	void __is_flip(bool is_flip) { is_flip_ = is_flip; }
	const ANIMATION_TYPE& __animation_type(void)const { return animation_type_; }
	bool __is_animation_end(void) { return is_animation_end_; }
	const D3DXVECTOR2& __Get_size(void)const{return size_;}
	void __color(D3DXCOLOR color){color_ = color;}
private:
	struct ANIMATION_TEXTURE_DATA
	{
		u32 _texture_id;
		u16 _division_width;
		u16 _division_height;

		ANIMATION_TEXTURE_DATA(u32 texture_id,u16 division_width,u16 division_height)
			:_texture_id(texture_id)
			,_division_width(division_width)
			,_division_height(division_height)
		{}
	};

	static const Animation::DATA* ANIMATION_DATA[ANIMATION_TYPE_MAX];
	static const u32 ANIMATION_DATA_SIZE_WAIT = 5 * 1;
	static const u32 ANIMATION_DATA_SIZE_RUN = 3 * 2;
	static const u32 ANIMATION_DATA_SIZE_JUMP = 3 * 2;
	static const u32 ANIMATION_DATA_SIZE_FALL = 3 * 1;
	static const u32 ANIMATION_DATA_SIZE_LIGHT_START = 1 * 1;
	static const u32 ANIMATION_DATA_SIZE_LIGHT_END = 1 * 1;
	static const u32 ANIMATION_DATA_SIZE_LIGHT = 6 * 1;
	static const u32 ANIMATION_DATA_SIZE_DAMAGE = 1 * 1;
	static const u32 ANIMATION_DATA_SIZE_GAME_START = 1 * 1;
	static const u32 ANIMATION_DATA_SIZE_GAME_END = 1 * 1;
	static const u32 ANIMATION_DATA_SIZE_DEAD = 9 * 1;
	static const u32 ANIMATION_DATA_SIZE_JOY = 7 * 1;

	static const u32 ANIMATION_DATA_SIZE[ANIMATION_TYPE_MAX];
	static const Animation::DATA WAIT_ANIMATION_DATA[ANIMATION_DATA_SIZE_WAIT];
	static const Animation::DATA RUN_ANIMATION_DATA[ANIMATION_DATA_SIZE_RUN];
	static const Animation::DATA JUMP_ANIMATION_DATA[ANIMATION_DATA_SIZE_JUMP];
	static const Animation::DATA FALL_ANIMATION_DATA[ANIMATION_DATA_SIZE_FALL];
	static const Animation::DATA LIGHT_START_ANIMATION_DATA[ANIMATION_DATA_SIZE_LIGHT_START];
	static const Animation::DATA LIGHT_END_ANIMATION_DATA[ANIMATION_DATA_SIZE_LIGHT_END];
	static const Animation::DATA LIGHT_ANIMATION_DATA[ANIMATION_DATA_SIZE_LIGHT];
	static const Animation::DATA DAMAGE_ANIMATION_DATA[ANIMATION_DATA_SIZE_DAMAGE];
	static const Animation::DATA GAME_START_ANIMATION_DATA[ANIMATION_DATA_SIZE_GAME_START];
	static const Animation::DATA GAME_END_ANIMATION_DATA[ANIMATION_DATA_SIZE_GAME_END];
	static const Animation::DATA DEAD_ANIMATION_DATA[ANIMATION_DATA_SIZE_DEAD];
	static const Animation::DATA JOY_ANIMATION_DATA[ANIMATION_DATA_SIZE_JOY];

	static const ANIMATION_TEXTURE_DATA TEXTURE_DATA[ANIMATION_TYPE_MAX];

	static const D3DXVECTOR2 DEFAULT_SIZE;
	D3DXVECTOR2 position_;
	D3DXVECTOR2 size_;
	bool		is_flip_;				// プレイヤーの向き
	Sprite*		player_;				// プレイヤースプライト
	Animation*	animation_;
	ANIMATION_TYPE animation_type_;
	bool is_animation_end_;
	D3DXCOLOR	color_;
};

#endif	// _OBJECT_PLAYER_H_

//---------------------------------- EOF --------------------------------------
