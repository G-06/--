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

	// get index
	u32 GetIndex(const D3DXVECTOR2& position,D3DXVECTOR2* index_position = nullptr);

	// load from file
	bool LoadFromFile(const s8* filename);

	// load from memory
	bool LoadFromMemory(const u8* memory);

	// accessor
	void __position(const D3DXVECTOR2& position) { position_ = position; }
	const D3DXVECTOR2& __size(void) { return size_; }

private:
	static const D3DXVECTOR2 SIZE;
	static const u32 DIVISION_WIDTH;
	static const u32 DIVISION_HEIGHT;

	MeshSprite* map_;
	u32 width_;
	u32 height_;
	u32* indexs_;
	D3DXVECTOR2 position_;
	D3DXVECTOR2 size_;
};

#endif	// _MAP_H_

//---------------------------------- EOF --------------------------------------
