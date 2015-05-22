//*****************************************************************************
//
// application
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class ApplicationSystemManager;
class SceneManager;

// HACK
class FontTexture;
class Sprite;
class Animation;
class TextBox;
class StageOffset;
class Stage;

//*****************************************************************************
// class definition
//*****************************************************************************
class Application : public Basic
{
public:
	// constructor
	Application(void);

	// destructor
	virtual ~Application(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

private:
	// scene manager
	SceneManager* scene_manager_;

	// is loop
	bool is_loop_;

	// HACK
	Sprite* sprite_;
	Stage* stage_;
	Animation* animation_;
	FontTexture* font_texture_;
	TextBox* text_box_;
	StageOffset* stage_offset_;
	D3DXVECTOR2 position_;
};

#endif	// _APPLICATION_H_

//---------------------------------- EOF --------------------------------------
