//*****************************************************************************
//
// title circle
//
// Author	: masato masuda
//
// ‰ñ‚Á‚Ä‚é‚â‚Â
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _TITLE_CIRCLE_H_
#define _TITLE_CIRCLE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"
#include "system/directx9/texture/texture.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Sprite;

//*****************************************************************************
// class definition
//*****************************************************************************
class TitleCircle : public Basic
{
public:
	// constructor
	TitleCircle(void);

	// destructor
	virtual ~TitleCircle(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	void AddRotation(const f32 rotation);

	// texture
	void __texture_id(const Texture::TEXTURE_ID& texture_id);

private:
	static const D3DXVECTOR2 DEFAULT_POSITION;
	static const D3DXVECTOR2 DEFAULT_SIZE;

	Sprite* sprite_;
};

#endif	// _TITLE_LUMINESCENCE_H_

//---------------------------------- EOF --------------------------------------
