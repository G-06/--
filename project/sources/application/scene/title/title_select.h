//*****************************************************************************
//
// title select
//
// Author	: masato masuda
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _TITLE_SELECT_H_
#define _TITLE_SELECT_H_

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
class TitleSelect : public Basic
{
public:
	// constructor
	TitleSelect(void);

	// destructor
	virtual ~TitleSelect(void);

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

#endif	// _TITLE_SELECT_H_

//---------------------------------- EOF --------------------------------------
