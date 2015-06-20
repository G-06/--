//*****************************************************************************
//
// normal stage
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _NORMAL_STAGE_H_
#define _NORMAL_STAGE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "stage.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class GamePlayer;
class Map;
class StageOffset;
class Gimmick;
class ObjectLightGauge;
class ObjectPlayerIcon;
class Pause;
class MessageWindow;

//*****************************************************************************
// class definition
//*****************************************************************************
class NormalStage : public Stage
{
public:
	// constructor
	NormalStage(const TYPE& type);

	// destructor
	virtual ~NormalStage(void);

	// initialize
	virtual bool Initialize(void);

	// uninitialize
	virtual void Uninitialize(void);

	// update
	virtual void Update(void);

	// draw
	virtual void Draw(void);

	// create factory
	virtual StageFactory* CreateFactory(void)const = 0;

	// collision chip
	void CollisionChip(void);
	void CollisionChip(u32 index,const D3DXVECTOR2& position);

	// collision gimmick
	void CollisionGimmick(void);

	// load from file
	bool LoadFromFile(const s8* filename);

	// load from memory
	bool LoadFromMemory(const s8* data);

	u32 FindWord(s8* dest,const s8* source,s8* words);

	// accessor
	bool __is_pause(void){return is_pause_;}

protected:
	GamePlayer* game_player_;
	Map* map_;
	StageOffset* stage_offset_;
	ObjectLightGauge* object_light_gauge_;
	ObjectPlayerIcon* object_player_icon_;
	std::list<Gimmick*> gimmick_container_;
	u32 time_count_;
	D3DXVECTOR2 position_;
	bool is_pause_;
	bool is_clear_;
	bool is_pause_input_;
	Pause* pause_;
	MessageWindow* message_window_;

private:
	static const D3DXVECTOR2 DEFAULT_LIGHT_GAUGE_POSITION;
	static const D3DXVECTOR2 DEFAULT_PLAYER_ICON_POSITION;
};

#endif	// _NORMAL_STAGE_H_

//---------------------------------- EOF --------------------------------------
