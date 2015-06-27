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
#include "application/scene/game/stage/stage_select.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class ObjectRecord;
class RecordBack;

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
	void __offset_position(D3DXVECTOR2 pos){off_position_=pos;};
	void __set_time(u32 time);
	void __set_position(D3DXVECTOR2 pos);

private:
	ObjectRecord* record_;
	RecordBack* back_;

	D3DXVECTOR2 off_position_;
};

#endif	// _select_record_H_

//---------------------------------- EOF --------------------------------------
