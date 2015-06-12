//*****************************************************************************
//
// stage
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _STAGE_H_
#define _STAGE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class StageFactory;

//*****************************************************************************
// class definition
//*****************************************************************************
class Stage : public Basic
{
public:
	enum TYPE
	{
		TYPE_SELECT = 0,
		TYPE_TUTORIAL,
		TYPE_MAX
	};

	// constructor
	Stage(const TYPE& type);

	// destructor
	virtual ~Stage(void);

	// initialize
	virtual bool Initialize(void) = 0;

	// uninitialize
	virtual void Uninitialize(void) = 0;

	// update
	virtual void Update(void) = 0;

	// draw
	virtual void Draw(void) = 0;

	// create factory
	virtual StageFactory* CreateFactory(void)const = 0;

	// accessor
	const TYPE& __type(void)const { return type_; }
	StageFactory* __next_stage_factory(void)const { return next_stage_factory_; }
	void __is_fade(bool is_fade) { is_fade_ = is_fade; }

protected:
	StageFactory* next_stage_factory_;
	bool is_fade_;

private:
	TYPE type_;
};

#endif	// _STAGE_H_

//---------------------------------- EOF --------------------------------------
