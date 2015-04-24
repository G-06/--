//*****************************************************************************
//
// font texture
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _FONT_TEXTURE_H_
#define _FONT_TEXTURE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"

//*****************************************************************************
// class definition
//*****************************************************************************
class FontTexture : public Basic
{
public:
	enum TYPE
	{
		TYPE_MS_GOTHIC = 0,
		TYPE_MS_MINTYO,
		TYPE_MEIRYO,
		TYPE_MEIRYO_UI,
		TYPE_MAX
	};

	// constructor
	FontTexture(const s8* character,const s16& size);
	FontTexture(const u32& character_code,const s16& size);

	// destructor
	virtual ~FontTexture(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// create
	bool Create(void);

	// accessor
	LPDIRECT3DTEXTURE9 __texture(void)const { return texture_; }
	const TYPE& __type(void)const { return type_; }
	const u32& __width(void)const { return width_; }
	const u32& __height(void)const { return height_; }
	const u32& __offset_y(void)const { return offset_y_; }

private:
	static const s8* FONT_TYPE_NAME[TYPE_MAX];

	LPDIRECT3DDEVICE9 device_;
	LPDIRECT3DTEXTURE9 texture_;
	u32 character_code_;
	s16 size_;
	s16 weight_;
	TYPE type_;

	u32 width_;
	u32 height_;
	u32 offset_y_;
};

#endif	// _FONT_TEXTURE_H_

//---------------------------------- EOF --------------------------------------
