//*****************************************************************************
//
// stage manager
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _STAGE_MANAGER_H_
#define _STAGE_MANAGER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Stage;
class StageFactory;
class Fade;

//*****************************************************************************
// class definition
//*****************************************************************************
class StageManager : public Basic
{
public:
	// constructor
	StageManager(void);

	// destructor
	virtual ~StageManager(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// accessor
	bool __is_error(void)const { return is_error_; }

private:
	Stage* current_stage_;
	Stage* next_stage_;
	Fade* fade_;
	bool is_error_;
};

#endif	// _STAGE_MANAGER_H_

//---------------------------------- EOF --------------------------------------
