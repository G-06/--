//*****************************************************************************
//
// effect
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _EFFECT_H_
#define _EFFECT_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************

//*****************************************************************************
// class definition
//*****************************************************************************
class Effect : public Basic
{
public:
	enum TYPE
	{
		TYPE_CHECK_POINT = 0,
		TYPE_MAX,
	};

	// constructor
	Effect(TYPE type);

	// destructor
	virtual ~Effect(void);

	// initialize
	virtual bool Initialize(void);

	// uninitialize
	virtual void Uninitialize(void);

	// update
	virtual void Update(void);

	// draw
	virtual void Draw(void);

	// accessor
	void __position(const D3DXVECTOR2& position) { position_ = position; }
	const D3DXVECTOR2& __position(void) { return position_; }
	void __offset_position(const D3DXVECTOR2& offset_position) { offset_position_ = offset_position; }
	TYPE __type(void)const { return type_; }
	bool __is_death(void)const { return is_death_; }
protected:
	D3DXVECTOR2 position_;
	D3DXVECTOR2 offset_position_;
	TYPE type_;
	bool is_death_;
};

#endif	// _EFFECT_H_

//---------------------------------- EOF --------------------------------------
