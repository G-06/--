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

		DATA(u32 frame,u32 next_index)
			:_frame(frame),
			_next_index(next_index) {}
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
	void Add(DATA* data,u32 size);

	// accessor
	void __current_index(const u32& current_index) { current_index_ = current_index; frame_count_ = 0; }
	const u32& __current_index(void)const { return current_index_; }

private:
	u32 frame_count_;
	u32 current_index_;
	std::vector<DATA> container_;
};

#endif	// _ANIMATION_H_

//---------------------------------- EOF --------------------------------------
