//*****************************************************************************
//
// map
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _MAP_H_
#define _MAP_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class MeshSprite;

//*****************************************************************************
// class definition
//*****************************************************************************
class Map : public Basic
{
public:
	// constructor
	Map(void);

	// destructor
	virtual ~Map(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// load from file
	bool LoadFromFile(const s8* filename);

	// load from memory
	bool LoadFromMemory(const u8* memory);

private:
	MeshSprite* map_;

};

#endif	// _MAP_H_

//---------------------------------- EOF --------------------------------------
