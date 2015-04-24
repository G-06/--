//*****************************************************************************
//
// scene title
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _SCENE_TITLE_H_
#define _SCENE_TITLE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "scene/scene.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class TitleBg;

//*****************************************************************************
// class definition
//*****************************************************************************
class SceneTitle : public Scene
{
public:
	// constructor
	SceneTitle(void);

	// destructor
	virtual ~SceneTitle(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// create factory
	SceneFactory* CreateFactory(void)const;

private:
	TitleBg* title_bg_;
};

#endif	// _SCENE_TITLE_H_

//---------------------------------- EOF --------------------------------------
