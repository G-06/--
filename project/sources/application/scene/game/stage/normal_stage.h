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
class ObjectPlayerLife;
class Pause;
class MessageWindow;
class GameBg;
class Effect;
class AssertEffectStart;
class AssertEffectClear;
class SelectRecord;
class Option;
class EffectMirror;
class EffectSkeleton;

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
	ObjectPlayerLife* object_player_life_;
	std::list<Gimmick*> gimmick_container_;
	std::list<Effect*> effect_container_;
	u32 time_count_;
	s32 effect_timer_;
	D3DXVECTOR2 position_;
	bool is_pause_;
	bool is_option_;
	bool is_clear_;
	bool is_start_;
	bool is_pause_input_;
	Pause* pause_;
	MessageWindow* message_window_;
	Option* option_;

	AssertEffectStart* assert_effect_start_;
	AssertEffectClear* assert_effect_clear_;
	SelectRecord* select_record_;
	GameBg* game_bg_;
	TYPE type_;

private:
	static const s32 EFFECT_STOCK_NUM = 20;

protected:
	bool gameover_;
	u32 time;
	EffectMirror* effect_mirror_[EFFECT_STOCK_NUM];
	EffectSkeleton* effect_skeleton_[EFFECT_STOCK_NUM];

private:
	static const D3DXVECTOR2 DEFAULT_LIGHT_GAUGE_POSITION;
	static const D3DXVECTOR2 DEFAULT_PLAYER_ICON_POSITION;
	static const D3DXVECTOR2 DEFAULT_PLAYER_LIFE_POSITION;

};

#endif	// _NORMAL_STAGE_H_

//---------------------------------- EOF --------------------------------------
