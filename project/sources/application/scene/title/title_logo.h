//*****************************************************************************
//
// title logo
//
// Author	: masato masuda
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

	void StartMove(void);

	void __dest_position(const D3DXVECTOR2& dest_position){dest_position_ = dest_position;}

private:
	static const D3DXVECTOR2 DEFAULT_POSITION;
	static const D3DXVECTOR2 DEFAULT_SIZE;
	Sprite* sprite_;

	D3DXVECTOR2	dest_position_;
	D3DXVECTOR2	target_position_;
	D3DXVECTOR2	old_position_;

	u32 dest_frame_;
	u32 now_frame_;
	bool is_move_;
};

#endif	// _TITLE_BG_H_

//---------------------------------- EOF --------------------------------------
