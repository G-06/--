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
#ifndef _SELECT_STAGE_NAME_H_
#define _SELECT_STAGE_NAME_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"
#include "application/scene/game/stage/stage_select.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Sprite;

//*****************************************************************************
// class definition
//*****************************************************************************
class StageName : public Basic
{
public:

	// constructor
	StageName(void);

	// destructor
	virtual ~StageName(void);

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

	//ステージ名テクスチャの設定
	void __set_name_texture(Stage::TYPE stage);

protected:
	static const D3DXVECTOR2 DEFAULT_POSITION;
	static const D3DXVECTOR2 DEFAULT_SIZE;
	static const D3DXVECTOR2 STAGE_SIZE;

	D3DXVECTOR2 size_;
	D3DXVECTOR2 offset_position_;
	Sprite* name_;
};

#endif	// _PLAYER_H_

//---------------------------------- EOF --------------------------------------
