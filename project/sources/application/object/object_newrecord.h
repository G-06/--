//*****************************************************************************
//
// obj new record
//
// Author		: taichi kitazawa
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _OBJECT_NEWRECORD_H_
#define _OBJECT_NEWRECORD_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"
#include "application/scene/game/stage/stage.h"
#include "system/directx9/texture/texture.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Sprite;

//*****************************************************************************
// class definition
//*****************************************************************************
class ObjectNewRecord : public Basic
{
public:
	// constructor
	ObjectNewRecord(void);

	// destructor
	virtual ~ObjectNewRecord(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	void __set_position(D3DXVECTOR2 position){position_=position;};


private:
	Sprite* sprite_;
	D3DXVECTOR2 position_;
};

#endif	// _OBJECT_NEWRECORD_H_

//---------------------------------- EOF --------------------------------------
