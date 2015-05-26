//*****************************************************************************
//
// animation
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _ANIMATION_H_
#define _ANIMATION_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"

//*****************************************************************************
// class definition
//*****************************************************************************
class Animation : public Basic
{
public:
	typedef struct DATA
	{
		u32 _frame;
		u32 _next_index;
		u32 _number;

		DATA(u32 frame,u32 next_index,u32 number)
			:_frame(frame)
			,_next_index(next_index)
			,_number(number) {}
	};

	// constructor
	Animation(void);

	// destructor
	virtual ~Animation(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// add
	void Add(const DATA* data,u32 size);

	// start
	void Start(u32 index);

	// stop
	void Stop(void);

	// accessor
	void __current_index(const u32& current_index) { current_index_ = current_index; frame_count_ = 0; }
	const u32& __current_index(void)const { return current_index_; }
	void __number(const u32& number) { number_ = number; frame_count_ = 0; }
	const u32& __number(void)const { return number_; }

private:
	u32 frame_count_;
	u32 current_index_;
	u32 number_;
	std::vector<DATA> container_;
	bool is_actitive;
};

#endif	// _ANIMATION_H_

//---------------------------------- EOF --------------------------------------
