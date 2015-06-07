//*****************************************************************************
//
// title select_frame
//
// Author	: masato masuda
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _TITLE_SELECT_FRAME_H_
#define _TITLE_SELECT_FRAME_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"
#include "system/directx9/texture/texture.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Sprite;
class Texture;

//*****************************************************************************
// class definition
//*****************************************************************************
class TitleSelectFrame : public Basic
{
public:
	// constructor
	TitleSelectFrame(void);

	// destructor
	virtual ~TitleSelectFrame(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	void __position(const D3DXVECTOR2& position);
	void __texture_id(const Texture::TEXTURE_ID& texture_id);


private:
	static const D3DXVECTOR2 DEFAULT_POSITION;
	static const D3DXVECTOR2 DEFAULT_SIZE;
	Sprite* sprite_;
};

#endif	// _TITLE_BG_H_

//---------------------------------- EOF --------------------------------------
