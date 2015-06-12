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
#ifndef _SELECT_ARROW_H_
#define _SELECT_ARROW_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class ArrowRight;
class ArrowLeft;

//*****************************************************************************
// class definition
//*****************************************************************************
class SelectArrow : public Basic
{
public:
	// constructor
	SelectArrow(void);

	// destructor
	virtual ~SelectArrow(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	//
	void __set_stage_id(u32 id){stage_id_ = id;}

private:
	ArrowRight* arrow_right_;
	ArrowLeft* arrow_left_;

	u32 stage_id_;
};

#endif	// _select_BG_H_

//---------------------------------- EOF --------------------------------------
