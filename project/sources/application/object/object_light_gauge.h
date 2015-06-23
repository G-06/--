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
	void __rate(f32 rate) { rate_ = rate; }

private:
	static const D3DXVECTOR2 GAUGE_SIZE;
	static const D3DXVECTOR2 GAUGE_POSITION;
	static const D3DXVECTOR2 GAUGE_FRAME_SIZE;
	static const D3DXVECTOR2 GAUGE_FRAME_POSITION;

	Sprite* gauge_;
	Sprite* gauge_frame_;
	Sprite* gauge_back_;
	D3DXVECTOR2 position_;
	f32 rate_;
};

#endif	// _OBJECT_LIGHT_GAUGE_H_

//---------------------------------- EOF --------------------------------------
