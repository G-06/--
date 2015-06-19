//*****************************************************************************
//
// assert effect
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _ASSERT_EFFECT_H_
#define _ASSERT_EFFECT_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************

//*****************************************************************************
// class definition
//*****************************************************************************
class AssertEffect : public Basic
{
public:
	enum TYPE
	{
		TYPE_ = 0,
		TYPE_MAX,
	};

	// constructor
	AssertEffect(TYPE type);

	// destructor
	virtual ~AssertEffect(void);

	// initialize
	virtual bool Initialize(void);

	// uninitialize
	virtual void Uninitialize(void);

	// update
	virtual void Update(void);

	// draw
	virtual void Draw(void);

	// accessor
	TYPE __type(void)const { return type_; }
	bool __is_assert(void) { return is_assert_; }

protected:
	TYPE type_;
	bool is_assert_;

};

#endif	// _ASSERT_EFFECT_H_

//---------------------------------- EOF --------------------------------------
