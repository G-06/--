//*****************************************************************************
//
// object_player_life
//
// Author	: masato masuda
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _OBJECT_PLAYER_LIFE_H_
#define _OBJECT_PLAYER_LIFE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class ObjectLife;

//*****************************************************************************
// class definition
//*****************************************************************************
class ObjectPlayerLife : public Basic
{
public:
	// constructor
	ObjectPlayerLife(void);

	// destructor
	virtual ~ObjectPlayerLife(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	static const u32 LIFE_MAX = 3;

	void __life(const s32 life){ life_ = life; }
	void __position(const D3DXVECTOR2 position);

private:
	static const D3DXVECTOR2 LIFE_SIZE;
	static const D3DXVECTOR2 LIFE_POSITION;

	D3DXVECTOR2 provision_position_;
	ObjectLife* life_icon_[LIFE_MAX];
	s32 life_;
};

#endif	// _OBJECT_LIGHT_GAUGE_H_

//---------------------------------- EOF --------------------------------------
