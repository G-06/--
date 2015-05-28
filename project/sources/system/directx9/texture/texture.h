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
		TEXTURE_ID_STAGE_BG,
		TEXTURE_ID_LOGO,
		TEXTURE_ID_LOGO_BG,
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
