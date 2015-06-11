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

	// jump
	void Jump(void);

	// run
	void Run(void);

	// stop
	void Wait(void);

	// light
	void Light(void);

	// 座標の取得
	const D3DXVECTOR2& __position(void)const{ return position_; }
	void __position(const D3DXVECTOR2& position){ position_ = position; }
	void __is_flip(bool is_flip) { is_flip_ = is_flip; }

private:
	void LightMode(bool is_light, bool is_right);

	enum ANIMATION_TYPE
	{
		ANIMATION_TYPE_WAIT = 0,
		ANIMATION_TYPE_RUN,
		ANIMATION_TYPE_LIGHT,
		ANIMATION_TYPE_MAX
	};

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

	static const Animation::DATA ANIMATION_DATA[];
	static const u32 ANIMATION_RUN_START;
	static const u32 ANIMATION_WAIT_START;
	static const u32 ANIMATION_LIGHT_START;
	static const ANIMATION_TEXTURE_DATA TEXTURE_DATA[ANIMATION_TYPE_MAX];

	D3DXVECTOR2 position_;
	bool		is_flip_;				// プレイヤーの向き
	Sprite*		player_;				// プレイヤースプライト
	Animation*	animation_;
	ANIMATION_TYPE animation_type_;
};

#endif	// _OBJECT_PLAYER_H_

//---------------------------------- EOF --------------------------------------
