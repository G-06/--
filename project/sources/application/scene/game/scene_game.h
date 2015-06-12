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
#include "application/object/stage_select.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Stage;
class StageOffset;
class GamePlayer;
class StageSelect;
class Fade;
class Map;

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

	//���̃X�e�[�W
	static void __next_stage(STAGE_ID next){next_stage_ = next;};

	//�X�e�[�W�̐؂�ւ�
	bool ChangeNextStage(void);

private:
	Stage* stage_;
	StageOffset* stage_offset_;
	GamePlayer* player_;
	Map* map_;
	StageSelect* stage_select_;
	Fade* fade_;

	STAGE_ID current_stage_;		// ������X�e�[�W�i�X�e�[�W�I���܂ށj
	static STAGE_ID next_stage_;		// ������X�e�[�W�i�X�e�[�W�I���܂ށj

};

#endif	// _SCENE_GAME_H_

//---------------------------------- EOF --------------------------------------
