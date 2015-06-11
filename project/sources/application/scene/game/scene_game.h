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
class Player;
class StageSelect;
class Fade;


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

	//次のステージ
	static void __next_stage(STAGE_ID next){next_stage_ = next;};

	//ステージの切り替え
	bool ChangeNextStage(void);

private:
	Stage* stage_;
	StageOffset* stage_offset_;
	Player* player_;
	StageSelect* stage_select_;
	Fade* fade_;


	STAGE_ID current_stage_;		// 今いるステージ（ステージ選択含む）
	static STAGE_ID next_stage_;		// 今いるステージ（ステージ選択含む）

};

#endif	// _SCENE_GAME_H_

//---------------------------------- EOF --------------------------------------
