//*****************************************************************************
//
// sprite
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _SPRITE_H_
#define _SPRITE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"
#include "system/directx9/texture/texture.h"

//*****************************************************************************
// class definition
//*****************************************************************************
class Sprite : public Basic
{
public:
	enum POINT
	{
		POINT_CENTER = 0,
		POINT_LEFT_UP,
		POINT_LEFT_MIDDLE,
		POINT_LEFT_DOWN,
		POINT_RIGHT_UP,
		POINT_RIGHT_MIDDLE,
		POINT_RIGHT_DOWN,
		POINT_MIDDLE_UP,
		POINT_MIDDLE_DOWN,
		POINT_MAX,
	};

	// constructor
	Sprite(void);

	// destructor
	virtual ~Sprite(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// draw
	void Draw(void);
	void Draw(const D3DXMATRIX& matrix);

	// set parameter
	void SetParameter(void);

	// accessor
	const D3DXVECTOR2& __position(void)const { return position_; }
	void __position(const D3DXVECTOR2& position) { position_ = position; }
	const f32& __rotation(void)const { return rotation_; }
	void __rotation(const f32& rotation) { rotation_ = rotation; }
	const D3DXVECTOR2& __size(void)const { return size_; }
	void __size(const D3DXVECTOR2& size) { size_ = size; }
	const POINT& __point(void)const { return point_; }
	void __point(const POINT& point) { point_ = point; }
	const D3DCOLOR& __color(void)const { return color_; }
	void __color(const D3DCOLOR& color) { color_ = color; }
	const f32& __left(void)const { return left_; }
	void __left(const f32& left) { left_ = left; }
	const f32& __right(void)const { return right_; }
	void __right(const f32& right) { right_ = right; }
	const f32& __top(void)const { return top_; }
	void __top(const f32& top) { top_ = top; }
	const f32& __bottom(void)const { return bottom_; }
	void __bottom(const f32& bottom) { bottom_ = bottom; }
	const Texture::TEXTURE_ID& __texture_id(void)const { return texture_id_; }
	void __texture_id(const Texture::TEXTURE_ID& texture_id) { texture_id_ = texture_id; }
	void __texture(LPDIRECT3DTEXTURE9 texture) { texture_ = texture; }

private:
	LPDIRECT3DDEVICE9 device_;
	LPDIRECT3DVERTEXBUFFER9 vertex_buffer_;
	LPDIRECT3DTEXTURE9 texture_;

	static const D3DXVECTOR2 DEFAULT_SIZE;
	static const D3DCOLOR DEFAULT_COLOR;
	static const D3DXVECTOR2 DEFAULT_POSITION;
	static const POINT DEFAULT_POINT;

	D3DXVECTOR2 position_;
	f32 rotation_;
	D3DXVECTOR2 scale_;

	D3DXVECTOR2 size_;
	D3DCOLOR color_;
	POINT point_;
	f32 left_;
	f32 right_;
	f32 top_;
	f32 bottom_;
	Texture::TEXTURE_ID texture_id_;
};

#endif	// _SPRITE_H_

//---------------------------------- EOF --------------------------------------
