//*****************************************************************************
//
// volume logo
//
// Author		: Ryotaro Arai
//				: masato masuda
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _VOLUME_LOGO_H_
#define _VOLUME_LOGO_H_

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
class VolumeLogo : public Basic
{
public:
	// constructor
	VolumeLogo(void);

	// destructor
	virtual ~VolumeLogo(void);

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

#endif	// _VOLUME_LOGO_H_

//---------------------------------- EOF --------------------------------------
