//*****************************************************************************
//
// key config special
//
// Author		: Ryotaro Arai
//				: masato masuda
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _KEY_CONFIG_SPECIAL_H_
#define _KEY_CONFIG_SPECIAL_H_

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
class KeyConfigSpecial : public Basic
{
public:
	// constructor
	KeyConfigSpecial(void);

	// destructor
	virtual ~KeyConfigSpecial(void);

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

	void SetAlpha(f32 alpha);

	void __set_button_number_texture(INPUT_EVENT button);
	void __position(const D3DXVECTOR2 position, const float offset_x);
	void __texture_id_frame(const Texture::TEXTURE_ID& texture_id);

private:

	OptionSpriteSmooth* special_button_;
	OptionSpriteSmooth* special_button_frame_;
	OptionSpriteSmooth* set_button_number_;
	OptionSpriteSmooth* set_button_number_frame_;
	OptionSpriteSmooth* set_button_number_back_;

	u32 current_key_event_;
};

#endif	// _KEY_CONFIG_SPECIAL_H_

//---------------------------------- EOF --------------------------------------
