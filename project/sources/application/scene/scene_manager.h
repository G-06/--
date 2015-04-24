//*****************************************************************************
//
// scene manager
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Scene;
class SceneFactory;
class Fade;

//*****************************************************************************
// class definition
//*****************************************************************************
class SceneManager : public Basic
{
public:
	// constructor
	SceneManager(void);

	// destructor
	virtual ~SceneManager(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);
private:
	Scene* current_scene_;
	Scene* next_scene_;
	Fade* fade_;
};

#endif	// _SCENE_MANAGER_H_

//---------------------------------- EOF --------------------------------------
