//*****************************************************************************
//
// logo
//
// Author		: taichi kitazawa
//				: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _LOGO_LOGO_H_
#define _LOGO_LOGO_H_

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
class Logo : public Basic
{
public:
	// constructor
	Logo(void);

	// destructor
	virtual ~Logo(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// start
	void Start(void);

	// accessor
	bool __is_end(void) { return is_end_; }
	bool __is_active(void) { return is_active_; }
private:
	static const D3DXVECTOR2 DEFAULT_POSITION;
	static const D3DXVECTOR2 DEFAULT_SIZE;
	static const u32 DEFAULT_DIVISION_WIDTH;
	static const u32 DEFAULT_DIVISION_HEIGHT;
	static const Animation::DATA ANIMATION_DATA[];

	Sprite* logo_neko_;		//ÉçÉS
	Animation* animation_;
	bool is_end_;
	bool is_active_;



};

#endif	// _TITLE_BG_H_

//---------------------------------- EOF --------------------------------------
