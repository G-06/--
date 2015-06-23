//*****************************************************************************
//
// game bg
//
// Author		: taichi kitazawa
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _GAME_BG_H_
#define _GAME_BG_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"
#include "stage/stage.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Sprite;
class ObjectBg;

//*****************************************************************************
// class definition
//*****************************************************************************
class GameBg : public Basic
{
public:
	// constructor
	GameBg(void);

	// destructor
	virtual ~GameBg(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	//ステージ教える
	void __SetTexture(Stage::TYPE type);
	void __SetPosition(D3DXVECTOR2 pos){old_position_ = position_;position_ = pos;};
	void ReSetUv(void);


private:
	ObjectBg* game_bg_far_;
	ObjectBg* game_bg_near_;

	D3DXVECTOR2 position_;
	D3DXVECTOR2 old_position_;
};

#endif	// _TITLE_BG_H_

//---------------------------------- EOF --------------------------------------
