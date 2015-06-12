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
		TEXTURE_ID_TEST = TEXTURE_TEST,
		TEXTURE_ID_ANIM_TEST,
		TEXTURE_ID_PLAYER,
		TEXTURE_ID_LIGHT,
		TEXTURE_ID_TITLE_BG,
		TEXTURE_ID_TITLE_LOGO,
		TEXTURE_ID_STAGE_BG,
		TEXTURE_ID_LOGO,
		TEXTURE_ID_LOGO_BG,
		TEXTURE_ID_TITLE_LUMINE,
		TEXTURE_ID_TITLE_SELECT_FRAME_000,
		TEXTURE_ID_TITLE_SELECT_FRAME_001,
		TEXTURE_ID_TITLE_STRING_TEST_A,
		TEXTURE_ID_GENERAL_WINDOW,
		TEXTURE_ID_STRING_YES,
		TEXTURE_ID_STRING_NO,
		TEXTURE_ID_OPTION_BG,
		TEXTURE_ID_VOLUME,
		TEXTURE_ID_CONFIG_BUTTON,
		TEXTURE_ID_VOLUME_BUTTON,
		TEXTURE_ID_OK_BUTTON,
		TEXTURE_ID_CANCEL_BUTTON,
		TEXTURE_ID_LIGHT_BUTTON,
		TEXTURE_ID_JUMP_BUTTON,
		TEXTURE_ID_PAUSE_BUTTON,
		TEXTURE_ID_BGM_LOGO,
		TEXTURE_ID_OPTION_LOGO,
		TEXTURE_ID_SE_LOGO,
		TEXTURE_ID_SLECT_FRAME_TST = TEXTURE_SELECT_FRAME_TST,
		TEXTURE_ID_STAGE_NAME_TST = TEXTURE_STAGE_NAME_TST,
		TEXTURE_ID_STAGE_NAME_TST1 = TEXTURE_STAGE_NAME_TST1,
		TEXTURE_ID_STAGE_NAME_TST2 = TEXTURE_STAGE_NAME_TST2,
		TEXTURE_ID_STAGE_IMAGE_TST = TEXTURE_STAGE_IMAGE_TST,
		TEXTURE_ID_SELECT_ARROW_RIGHT = TEXTURE_SELECT_ARROW_RIGHT,
		TEXTURE_ID_SELECT_ARROW_LEFT = TEXTURE_SELECT_ARROW_LEFT,
		TEXTURE_ID_NUMBER = TEXTURE_NUMBER,
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
	LPDIRECT3DTEXTURE9 texture_container_[TEXTURE_ID_MAX - TEXTURE_ID_TEST];
};

#endif	// _TEXTURE_H_

//---------------------------------- EOF --------------------------------------
