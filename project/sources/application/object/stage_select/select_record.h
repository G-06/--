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
class Number;
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
	void __set_stage_id(Stage::TYPE id){stage_id_ = id;};
	void __offset_position(const D3DXVECTOR2& offset_position) { offset_position_ = offset_position; };
	void __set_time(u32 time);
	void __set_position(D3DXVECTOR2 pos);


private:

	Stage::TYPE stage_id_;
	static const u32 TEXTURE_MAX = 8;

	u32 time_;			//reko-do
	Number* number_[TEXTURE_MAX];	//jikann 
	D3DXVECTOR2 offset_position_;
	RecordBack* record_back_;		//É^ÉCÉ}Å[îwåi
	D3DXVECTOR2 def_position;


};

#endif	// _select_record_H_

//---------------------------------- EOF --------------------------------------
