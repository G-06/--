//*****************************************************************************
//
// object light gauge
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _OBJECT_LIGHT_GAUGE_H_
#define _OBJECT_LIGHT_GAUGE_H_

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
class ObjectLightGauge : public Basic
{
public:
	// constructor
	ObjectLightGauge(void);

	// destructor
	virtual ~ObjectLightGauge(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// accessor
	void __position(const D3DXVECTOR2& position) { position_ = position; }
	const D3DXVECTOR2& __size(void) { return size_; }
	void __rate(f32 rate) { rate_ = rate; }
private:
	static const D3DXVECTOR2 SIZE;
	static const u32 DIVISION_WIDTH;
	static const u32 DIVISION_HEIGHT;

	Sprite* gauge_;
	D3DXVECTOR2 position_;
	D3DXVECTOR2 size_;
	f32 rate_;
};

#endif	// _OBJECT_START_POINT_H_

//---------------------------------- EOF --------------------------------------
