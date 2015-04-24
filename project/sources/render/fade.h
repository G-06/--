//*****************************************************************************
//
// fade
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _FADE_H_
#define _FADE_H_

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
class Fade : public Basic
{
public:
	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_IN,
		TYPE_OUT,
		TYPE_FADE,
		TYPE_MAX
	};

	// constructor
	Fade(void);

	// destructor
	virtual ~Fade(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// start
	void Start(const TYPE& type);

	// accessor
	const u32& __frame(void)const { return frame_; }
	void __frame(const u32& frame) { frame_ = frame; }
	const TYPE& __type(void) { return type_; }

private:
	Sprite* sprite_;
	f32 alpha_;
	f32 rate_;
	u32 frame_;
	TYPE type_;
};

#endif	// _SPRITE_H_

//---------------------------------- EOF --------------------------------------
