//*****************************************************************************
//
// obj bg
//
// Author		: taichi kitazawa
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _OBJECT_BG_H_
#define _OBJECT_BG_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"
#include "application/scene/game/stage/stage.h"
#include "system/directx9/texture/texture.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Sprite;

//*****************************************************************************
// class definition
//*****************************************************************************
class ObjectBg : public Basic
{
public:
	// constructor
	ObjectBg(void);

	// destructor
	virtual ~ObjectBg(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	//テクスチャ設置
	void __SetTexture(Texture::TEXTURE_ID texture);
	void __Set_move(D3DXVECTOR2 move){ move_.x += move.x; move_.y += move.y;};
	void ReSetUv(void);


private:
	Sprite* bg_;
	D3DXVECTOR2 uv_x_;	//横のuv x=right y=left
	D3DXVECTOR2 uv_y_;	//縦のuv x=top y=bottom
	D3DXVECTOR2 move_;

};

#endif	// _TITLE_BG_H_

//---------------------------------- EOF --------------------------------------
