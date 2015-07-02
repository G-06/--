//*****************************************************************************
//
// scene logo
//
// Author		: taichi kitazawa
//				: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _SCENE_LOGO_H_
#define _SCENE_LOGO_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "scene/scene.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Logo;
class LogoBg;

//*****************************************************************************
// class definition
//*****************************************************************************
class SceneLogo : public Scene
{
public:
	// constructor
	SceneLogo(void);

	// destructor
	virtual ~SceneLogo(void);

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
	Logo* logo_neko_;
	LogoBg* logo_bg_;

	u32 frame_count_;
	u32 end_count_;
};

#endif	// _SCENE_LOGO_H_

//---------------------------------- EOF --------------------------------------
