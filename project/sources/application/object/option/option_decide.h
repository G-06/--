//*****************************************************************************
//
// option decide
//
// Author	: masato masuda
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _OPTION_DECIDE_H_
#define _OPTION_DECIDE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"
#include "system/system.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class OptionSpriteSmooth;

//*****************************************************************************
// class definition
//*****************************************************************************
class OptionDecide : public Basic
{
public:
	// constructor
	OptionDecide(void);

	// destructor
	virtual ~OptionDecide(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// ‘I‘ð
	void Select(bool is_select);

	void __position(const D3DXVECTOR2 position, const float offset_x);
	void __texture_id_frame(const Texture::TEXTURE_ID& texture_id);

private:
	OptionSpriteSmooth* sprite_;
	OptionSpriteSmooth* sprite_frame_;
};

#endif	// _OPTION_DECIDE_H_

//---------------------------------- EOF --------------------------------------
