//*****************************************************************************
//
// ステージセレクトのステージの枠
//
// Author		: kitazawa taichi
//
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _SELECT_RECORD_BACK_H_
#define _SELECT_RECORD_BACK_H_

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
class RecordBack : public Basic
{
public:

	// constructor
	RecordBack(void);

	// destructor
	virtual ~RecordBack(void);

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
	static const D3DXVECTOR2 DEFAULT_POSITION;
	static const D3DXVECTOR2 DEFAULT_SIZE;
	static const D3DXVECTOR2 STAGE_SIZE;

	D3DXVECTOR2 size_;
	D3DXVECTOR2 offset_position_;
	Sprite* record_back_;
};

#endif	// _PLAYER_H_

//---------------------------------- EOF --------------------------------------
