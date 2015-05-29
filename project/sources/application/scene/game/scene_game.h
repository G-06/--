//*****************************************************************************
//
// scene game
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _SCENE_GAME_H_
#define _SCENE_GAME_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "scene/scene.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Stage;
class StageOffset;
class Player;

//*****************************************************************************
// class definition
//*****************************************************************************
class SceneGame : public Scene
{
public:
	// constructor
	SceneGame(void);

	// destructor
	virtual ~SceneGame(void);

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
	Stage* stage_;
	StageOffset* stage_offset_;
	Player* player_;
};

#endif	// _SCENE_GAME_H_

//---------------------------------- EOF --------------------------------------
