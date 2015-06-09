//*****************************************************************************
//
// mesh sprite
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _MESH_SPRITE_H_
#define _MESH_SPRITE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"
#include "system/directx9/texture/texture.h"

//*****************************************************************************
// class definition
//*****************************************************************************
class MeshSprite : public Basic
{
public:
	// constructor
	MeshSprite(u32 width_count,u32 height_count);

	// destructor
	virtual ~MeshSprite(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// draw
	void Draw(void);
	void Draw(const D3DXMATRIX& matrix);

	// set parameter
	void SetParameter(void);

	// set index
	void SetIndex(u32 x,u32 y,u32 index);

	// accessor
	const D3DXVECTOR2& __position(void)const { return position_; }
	void __position(const D3DXVECTOR2& position) { position_ = position; }
	const f32& __rotation(void)const { return rotation_; }
	void __rotation(const f32& rotation) { rotation_ = rotation; }
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
	void __index(const s32& index) { index_ = index; }
	void __division_width(const u32& division_width) { division_width_ = division_width; }
	void __division_height(const u32& division_height) { division_height_ = division_height; }
	bool __is_flip(void)const { return is_flip_; }
	void __is_flip(bool is_flip) { is_flip_ = is_flip; }
	void __width(f32 width) { width_ = width; }
	void __height(f32 height) { height_ = height; }
private:
	LPDIRECT3DDEVICE9 device_;
	LPDIRECT3DVERTEXBUFFER9 vertex_buffer_;
	LPDIRECT3DINDEXBUFFER9 index_buffer_;
	LPDIRECT3DTEXTURE9 texture_;

	static const D3DXVECTOR2 DEFAULT_SIZE;
	static const D3DCOLOR DEFAULT_COLOR;
	static const D3DXVECTOR2 DEFAULT_POSITION;

	D3DXVECTOR2 position_;
	f32 rotation_;
	D3DXVECTOR2 scale_;

	D3DCOLOR color_;
	POINT point_;
	f32 left_;
	f32 right_;
	f32 top_;
	f32 bottom_;
	Texture::TEXTURE_ID texture_id_;
	s32 index_;
	bool is_flip_;

	f32 width_;
	f32 height_;
	u32 width_count_;
	u32 height_count_;
	u32 division_width_;
	u32 division_height_;
	u32 vertex_count_;
	u32 index_count_;
	u32* indexs_;
};

#endif	// _MESH_SPRITE_H_

//---------------------------------- EOF --------------------------------------
