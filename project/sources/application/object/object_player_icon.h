//*****************************************************************************
//
// object player icon
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _OBJECT_PLAYER_ICON_H_
#define _OBJECT_PLAYER_ICON_H_

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
class ObjectPlayerIcon : public Basic
{
public:
	// constructor
	ObjectPlayerIcon(void);

	// destructor
	virtual ~ObjectPlayerIcon(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	enum ICON_TYPE{
		ICON_TYPE_NORMAL = 0,
		ICON_TYPE_SMILE,
		ICON_TYPE_CRY,
		ICON_TYPE_ANGER,
		ICON_TYPE_MAX
	};

	// accessor
	void __position(const D3DXVECTOR2& position) { position_ = position; }
	void __animation_index(const ICON_TYPE type);

private:
	static const D3DXVECTOR2 DEFAULT_SIZE;
	static const Animation::DATA ANIMATION_DATA[];
	static const u32 DIVISION_WIDTH;
	static const u32 DIVISION_HEIGHT;

	Sprite* sprite_;
	Animation* animation_;
	D3DXVECTOR2 position_;
};

#endif	// _OBJECT_LIGHT_GAUGE_H_

//---------------------------------- EOF --------------------------------------
