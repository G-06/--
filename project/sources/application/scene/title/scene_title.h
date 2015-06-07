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
class TitleSelect;
class TitleSelectFrame;

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

	typedef struct _TITLE_SELECT{
		TitleSelect*	select_;
		TitleSelect*	frame_;
	} TITLE_SELECT;

	static const u32 GO_LOGO_FRAME;
	static const u32 SELECT_MAX = 3;
	TitleBg* title_bg_;
	TitleLogo* title_logo_;
	TITLE_SELECT title_select_[SELECT_MAX];

	u32 frame_count_;		// ロゴに戻るカウンター
	s32 current_select_;	// 選択中の選択肢
};

#endif	// _SCENE_TITLE_H_

//---------------------------------- EOF --------------------------------------
