//*****************************************************************************
//
// stage select reko-do
//
// Author		: taichi kitazawa
//
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _SELECT_RECORD_H_
#define _SELECT_RECORD_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"
#include "application/object/stage_select.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Number;

//*****************************************************************************
// class definition
//*****************************************************************************
class SelectRecord : public Basic
{
public:
	// constructor
	SelectRecord(void);

	// destructor
	virtual ~SelectRecord(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	//
	void __set_stage_id(STAGE_ID id){stage_id_ = id;};
	void __offset_position(const D3DXVECTOR2& offset_position) { offset_position_ = offset_position; }
	void __set_time(u32 time);

private:

	STAGE_ID stage_id_;

	u32 time_;			//reko-do
	Number* number_[4];	//jikann 
	D3DXVECTOR2 offset_position_;



};

#endif	// _select_BG_H_

//---------------------------------- EOF --------------------------------------
