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
#ifndef _SELECT_NUMBER_H_
#define _SELECT_NUMBER_H_

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
class Number : public Basic
{
public:
	// constructor
	Number(void);

	// destructor
	virtual ~Number(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	void __Set_position(D3DXVECTOR2 pos){position_ = pos;};
	void __Set_index(u32 index){index_ = index;};

private:

	Sprite* number_;
	D3DXVECTOR2 position_;
	u32 index_;


};

#endif	// _select_BG_H_

//---------------------------------- EOF --------------------------------------
