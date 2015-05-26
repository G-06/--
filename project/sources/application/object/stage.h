//*****************************************************************************
//
// stage
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _STAGE_H_
#define _STAGE_H_

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
class Stage : public Basic
{
public:
	// constructor
	Stage(void);

	// destructor
	virtual ~Stage(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// accessor
	//void __size(const D3DXVECTOR2& size) { size_ = size; }
	const D3DXVECTOR2& __size(void)const { return size_; }
	void __offset_position(const D3DXVECTOR2& offset_position) { offset_position_ = offset_position; }

protected:
	static const D3DXVECTOR2 STAGE_SIZE;
	D3DXVECTOR2 size_;
	D3DXVECTOR2 offset_position_;
	Sprite* bg_;
};

#endif	// _STAGE_H_

//---------------------------------- EOF --------------------------------------
