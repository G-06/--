//*****************************************************************************
//
// object_life
//
// Author	: masato masuda
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _OBJECT_LIFE_H_
#define _OBJECT_LIFE_H_

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
class ObjectLife : public Basic
{
public:
	// constructor
	ObjectLife(void);

	// destructor
	virtual ~ObjectLife(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// ligfe_
	void __is_life(const bool is_life){ is_life_ = is_life; }
	bool __is_life(void){ return is_life_; }

	void __position(const D3DXVECTOR2 position);
	void __size(const D3DXVECTOR2 size);

private:
	static const D3DXVECTOR2 LIFE_SIZE;
	static const D3DXVECTOR2 LIFE_POSITION;

	Sprite*		life_;
	bool		is_life_;
	D3DXVECTOR2	size_;

};

#endif	// _OBJECT_LIGHT_GAUGE_H_

//---------------------------------- EOF --------------------------------------
