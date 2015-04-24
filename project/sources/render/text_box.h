//*****************************************************************************
//
// text box
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _TEXT_BOX_H_
#define _TEXT_BOX_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"
#include "system/directx9/font/font_texture.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Sprite;

//*****************************************************************************
// class definition
//*****************************************************************************
class TextBox : public Basic
{
public:
	// constructor
	TextBox(const FontTexture::TYPE& font_type,const u32& font_size);

	// destructor
	virtual ~TextBox(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// draw
	void Draw(void);

	// print
	void Print(const s8* format,...);

	// print
	void Print(const s8* format,D3DCOLOR font_color,...);

	// clear
	void Clear(void);

	// reset
	void Reset(void);

	// restart
	void Restart(void);

	// accessor
	const D3DXVECTOR2& __position(void)const { return position_; }
	void __position(const D3DXVECTOR2& position) { position_ = position; }
	void __show_speed(const u32& show_speed) { show_speed_ = show_speed; }
	const D3DCOLOR& __font_color(void)const { return font_color_; }
	const D3DCOLOR __font_color(const D3DCOLOR& font_color) { D3DCOLOR ret = font_color_;font_color_ = font_color; return ret; }

private:
	static const u32 STRING_MAX = 1024;
	LPDIRECT3DDEVICE9 device_;

	D3DCOLOR font_color_;
	u32 font_size_;
	FontTexture::TYPE font_type_;

	D3DXVECTOR2 position_;
	f32 rotation_;
	D3DXVECTOR2 scale_;

	D3DXVECTOR2 size_;
	s8 string_[STRING_MAX];
	Sprite* sprites_[STRING_MAX];
	std::map<u32,FontTexture*> font_texture_container_;
	u32 offset_x_;
	u32 offset_y_;
	u32 string_count_;
	u32 string_length_;

	u32 show_speed_;
	u32 show_count_;
	u32 frame_count_;
};

#endif	// _TEXT_BOX_H_

//---------------------------------- EOF --------------------------------------
