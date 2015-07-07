//*****************************************************************************
//
// keyconfig logo
//
// Author		: Ryotaro Arai
//				: masato masuda
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _KEYCONFIG_LOGO_H_
#define _KEYCONFIG_LOGO_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class OptionSpriteSmooth;

//*****************************************************************************
// class definition
//*****************************************************************************
class KeyconfigLogo : public Basic
{
public:
	// constructor
	KeyconfigLogo(void);

	// destructor
	virtual ~KeyconfigLogo(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	void __position(const D3DXVECTOR2 position);

private:
	OptionSpriteSmooth* sprite_;
};

#endif	// _KEYCONFIG_LOGO_H_

//---------------------------------- EOF --------------------------------------
