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
class TitleLogo;

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
	static const u32 GO_LOGO_FRAME;
	TitleBg* title_bg_;
	TitleLogo* title_logo_;
	u32 frame_count_;		//ロゴに戻るカウンター
};

#endif	// _SCENE_TITLE_H_

//---------------------------------- EOF --------------------------------------
