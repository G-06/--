//*****************************************************************************
//
// stage select bg
//
// Author		: taichi kitazawa
//
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _SELECT_BG_H_
#define _SELECT_BG_H_

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
class SelectBg : public Basic
{
public:
	// constructor
	SelectBg(void);

	// destructor
	virtual ~SelectBg(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	void __set_distmove(f32 move){ distmove_ += move;};

private:
	Sprite* bg_;
	D3DXVECTOR2 uv_;
	f32 move_;
	f32 distmove_;

};

#endif	// _select_BG_H_

//---------------------------------- EOF --------------------------------------
