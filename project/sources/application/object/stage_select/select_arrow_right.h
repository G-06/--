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
#ifndef _SELECT_ARROW_RIGHT_H_
#define _SELECT_ARROW_RIGHT_H_

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
class ArrowRight : public Basic
{
public:
	// constructor
	ArrowRight(void);

	// destructor
	virtual ~ArrowRight(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	//透明にしたりしなかったり
	void __Alpha_On(void);
	void __Alpha_Off(void);

private:
	Sprite* arrow_right_;
	u32 time_;		//点滅する時間をみるもの
	u32 alpha_;		//アルファ値


};

#endif	// _select_BG_H_

//---------------------------------- EOF --------------------------------------
