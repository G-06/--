//*****************************************************************************
//
// texture
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"
#include "../resources/resource.h"

//*****************************************************************************
// class definition
//*****************************************************************************
class Texture : public Basic
{
public:
	enum TEXTURE_ID
	{
		TEXTURE_ID_NONE = -1,
		// general
		TEXTURE_ID_DOT = TEXTURE_DOT,
		TEXTURE_ID_GENERAL_NUMBER,
		TEXTURE_ID_GENERAL_WINDOW,
		TEXTURE_ID_GENERAL_STRING_YES,
		TEXTURE_ID_GENERAL_STRING_NO,
		TEXTURE_ID_NYAS_STAND,
		TEXTURE_ID_NYAS_RUN,
		TEXTURE_ID_NYAS_JUMP,
		TEXTURE_ID_NYAS_FALL,
		TEXTURE_ID_NYAS_LIGHT_BEGIN,
		TEXTURE_ID_NYAS_LIGHT_END,
		TEXTURE_ID_NYAS_LIGHT,
		TEXTURE_ID_NYAS_DAMAGE,
		TEXTURE_ID_NYAS_START,
		TEXTURE_ID_NYAS_CLEAR,
		// logo
		TEXTURE_ID_TEAM_LOGO,
		// title
		TEXTURE_ID_TITLE_BG,
		TEXTURE_ID_TITLE_LOGO,
		TEXTURE_ID_TITLE_CIRCLE,
		TEXTURE_ID_TITLE_LUMINESCENCE,
		TEXTURE_ID_TITLE_SELECT_FRAME_000,
		TEXTURE_ID_TITLE_SELECT_FRAME_001,
		TEXTURE_ID_TITLE_SELECT_FRAME_002,
		TEXTURE_ID_TITLE_STRING_PUSH_START,
		TEXTURE_ID_TITLE_STRING_GAME_START,
		TEXTURE_ID_TITLE_STRING_OPTION,
		TEXTURE_ID_TITLE_STRING_GAME_END,
		TEXTURE_ID_TITLE_STRING_CONFIRM_END,
		// stage_select
		TEXTURE_ID_SELECT_BG,
		TEXTURE_ID_SELECT_STAGE_WINDOW,
		TEXTURE_ID_SELECT_STRING_TUTORIAL,
		TEXTURE_ID_SELECT_STRING_STAGE_1,
		TEXTURE_ID_SELECT_STRING_STAGE_2,
		TEXTURE_ID_SELECT_STRING_STAGE_3,
		TEXTURE_ID_SELECT_STRING_STAGE_4,
		TEXTURE_ID_SELECT_STRING_STAGE_5,
		TEXTURE_ID_SELECT_STRING_STAGE_6,
		TEXTURE_ID_SELECT_STRING_STAGE_7,
		TEXTURE_ID_SELECT_STRING_STAGE_8,
		TEXTURE_ID_SELECT_STRING_STAGE_9,
		TEXTURE_ID_SELECT_STRING_STAGE_10,
		TEXTURE_ID_SELECT_IMAGE_TUTORIAL,
		TEXTURE_ID_SELECT_IMAGE_STAGE_1,
		TEXTURE_ID_SELECT_IMAGE_STAGE_2,
		TEXTURE_ID_SELECT_IMAGE_STAGE_3,
		TEXTURE_ID_SELECT_IMAGE_STAGE_4,
		TEXTURE_ID_SELECT_IMAGE_STAGE_5,
		TEXTURE_ID_SELECT_IMAGE_STAGE_6,
		TEXTURE_ID_SELECT_IMAGE_STAGE_7,
		TEXTURE_ID_SELECT_IMAGE_STAGE_8,
		TEXTURE_ID_SELECT_IMAGE_STAGE_9,
		TEXTURE_ID_SELECT_IMAGE_STAGE_10,
		TEXTURE_ID_SELECT_ARROW_LEFT,
		TEXTURE_ID_SELECT_ARROW_RIGHT,
		TEXTURE_ID_SELECT_TIME_FRAME,
		TEXTURE_ID_SELECT_STRING_BEST_TIME,
		TEXTURE_ID_SELECT_STRING_STAGE_OK,
		TEXTURE_ID_SELECT_STRING_RETURN_TITLE,
		// option
		TEXTURE_ID_OPTION_OPTION_WINDOW,
		TEXTURE_ID_OPTION_STRING_SOUND_CONFIG,
		TEXTURE_ID_OPTION_STRING_KEY_CONFIG,
		TEXTURE_ID_OPTION_BGM_BAR,
		TEXTURE_ID_OPTION_SE_BAR,
		TEXTURE_ID_OPTION_BGM_BAR_FRAME,
		TEXTURE_ID_OPTION_BGM_BAR_BACK,
		TEXTURE_ID_OPTION_STRING_BGM_VOLUME,
		TEXTURE_ID_OPTION_STRING_SE_VOLUME,
		TEXTURE_ID_OPTION_STRING_CONFIG,
		TEXTURE_ID_OPTION_STRING_OP_DECIDE,
		TEXTURE_ID_OPTION_STRING_OP_CANCEL,
		TEXTURE_ID_OPTION_STRING_OP_JUMP,
		TEXTURE_ID_OPTION_STRING_OP_SPECIAL,
		TEXTURE_ID_OPTION_STRING_OP_PAUSE,
		TEXTURE_ID_OPTION_STRING_DESIDE,
		TEXTURE_ID_STRING_OP_CONFIRM_SAVE,
		TEXTURE_ID_STRING_OP_CONFIRM_CANCEL,
		// game
		TEXTURE_ID_GAME_START_POINT,
		TEXTURE_ID_GAME_GOAL_POINT,
		TEXTURE_ID_GAME_CHECK_POINT,
		TEXTURE_ID_MOVE_GROUND,
		TEXTURE_ID_DEATH_GROUND,
		TEXTURE_ID_DISAPPEAR_GROUND,
		TEXTURE_ID_LENS,

		TEXTURE_ID_GAME_NYAS_ICON,
		TEXTURE_ID_GAME_LIGHT_GAUGE_FRAME,
		TEXTURE_ID_GAME_LIGHT_GAUGE,
		TEXTURE_ID_GAME_LIGHT_GAUGE_BACK,
		TEXTURE_ID_GAME_LIFE,
		TEXTURE_ID_GAME_EFFECT_HIT,
		TEXTURE_ID_GAME_STRING_NEW_RECORD,
		TEXTURE_ID_GAME_STRING_START,
		TEXTURE_ID_GAME_STRING_CLEAR,
		TEXTURE_ID_GAME_STRING_CHECK_POINT,
		// pause
		TEXTURE_ID_PAUSE_WINDOW,
		TEXTURE_ID_PAUSE_STRING_PAUSE_OPTION,
		TEXTURE_ID_PAUSE_STRING_PAUSE_RETURN,
		TEXTURE_ID_PAUSE_STRING_PAUSE_TITLE_BACK,
		TEXTURE_ID_PAUSE_STRING_PAUSE_SELECT_BACK,
		TEXTURE_ID_PAUSE_STRUNG_CONFIRM_TITLE,
		TEXTURE_ID_PAUSE_STRUNG_CONFIRM_SELECT,
		// game bg
		TEXTURE_ID_GAME_BG_FAR_000,
		TEXTURE_ID_GAME_BG_NEAR_000,
		TEXTURE_ID_GAME_BG_FAR_001,
		TEXTURE_ID_GAME_BG_NEAR_001,
		TEXTURE_ID_GAME_BG_FAR_002,
		TEXTURE_ID_GAME_BG_NEAR_002,
		TEXTURE_ID_GAME_BG_FAR_TUTORIAL,
		TEXTURE_ID_GAME_BG_MIDDLE_000,
		// map
		TEXTURE_ID_MAP_000,
		TEXTURE_ID_MAP_001,
		TEXTURE_ID_MAP_002,
		// option
		TEXTURE_ID_OPTION_KEY_01,
		TEXTURE_ID_OPTION_KEY_02,
		TEXTURE_ID_OPTION_KEY_03,
		TEXTURE_ID_OPTION_KEY_04,
		TEXTURE_ID_OPTION_KEY_05,
		TEXTURE_ID_OPTION_KEY_06,
		TEXTURE_ID_OPTION_KEY_07,
		TEXTURE_ID_OPTION_KEY_08,
		TEXTURE_ID_OPTION_KEY_09,
		TEXTURE_ID_OPTION_KEY_10,
		TEXTURE_ID_OPTION_KEY_11,
		TEXTURE_ID_OPTION_KEY_12,
		TEXTURE_ID_OPTION_KEY_13,
		TEXTURE_ID_OPTION_KEY_14,
		TEXTURE_ID_OPTION_KEY_15,

		TEXTURE_ID_EFFECT_LIGHTNING,
		TEXTURE_ID_EFFECT_NYAS_DEAD,
		TEXTURE_ID_EFFECT_MIRROR,
		TEXTURE_ID_EFFECT_SKELETON,
		TEXTURE_ID_EFFECT_LOCUS,
		TEXTURE_ID_EFFECT_LENS,
		TEXTURE_ID_MAX
	};

	// constructor
	Texture(void);

	// destructor
	virtual ~Texture(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// get texture
	LPDIRECT3DTEXTURE9 GetTexture(const TEXTURE_ID& texture_id)const;

private:
	LPDIRECT3DDEVICE9 device_;
	LPDIRECT3DTEXTURE9 texture_container_[TEXTURE_ID_MAX - TEXTURE_ID_DOT];
};

#endif	// _TEXTURE_H_

//---------------------------------- EOF --------------------------------------
