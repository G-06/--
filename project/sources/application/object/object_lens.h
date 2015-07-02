//*****************************************************************************
//
// object lens
//
// Author		: Haruki Saito
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _OBJECT_LENS_H_
#define _OBJECT_LENS_H_

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
class ObjectLens : public Basic
{
public:
	// constructor
	ObjectLens(void);

	// destructor
	virtual ~ObjectLens(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// show
	void Show(bool is_show);

	// accessor
	void __position(const D3DXVECTOR2& position) { position_ = position; }
	const D3DXVECTOR2& __size(void) { return size_; }


private:
	static const D3DXVECTOR2 SIZE;
	static const u32 DIVISION_WIDTH;
	static const u32 DIVISION_HEIGHT;

	Sprite* object_lens_;
	D3DXVECTOR2 position_;
	D3DXVECTOR2 size_;

};

#endif	// _object_lens_H_

//---------------------------------- EOF --------------------------------------
