//*****************************************************************************
//
// title logo
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _TITLE_LOGO_H_
#define _TITLE_LOGO_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Sprite;

//*****************************************************************************
// class definition
//*****************************************************************************
class TitleLogo : public Basic
{
public:
	// constructor
	TitleLogo(void);

	// destructor
	virtual ~TitleLogo(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);
private:
	static const D3DXVECTOR2 DEFAULT_POSITION;
	static const D3DXVECTOR2 DEFAULT_SIZE;
	Sprite* sprite_;
};

#endif	// _TITLE_BG_H_

//---------------------------------- EOF --------------------------------------
