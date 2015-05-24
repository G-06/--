//*****************************************************************************
//
// application
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class SceneManager;
class FrameController;

//*****************************************************************************
// class definition
//*****************************************************************************
class Application : public Basic
{
public:
	// constructor
	Application(void);

	// destructor
	virtual ~Application(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	bool __is_loop(void)const { return is_loop_; }
private:
	SceneManager* scene_manager_;
	FrameController* frame_controller_;
	bool is_loop_;
};

#endif	// _APPLICATION_H_

//---------------------------------- EOF --------------------------------------
