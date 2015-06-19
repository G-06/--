//*****************************************************************************
//
// gimmick チュートリアルてきすと
//
// Author		: kitazawa taichi
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _GIMMICK_TUTORIAL_TEXT_H_
#define _GIMMICK_TUTORIAL_TEXT_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "gimmick.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class TextBox;

//*****************************************************************************
// class definition
//*****************************************************************************
class GimmickTutorialText : public Gimmick
{
public:
	struct DATA
	{
		u32 _priority;
		bool _is_hit;
	};

	// constructor
	GimmickTutorialText(void);

	// destructor
	virtual ~GimmickTutorialText(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	void* GetPointer(void);
	// accessor
	u32 __priority(void)const { return data_._priority; }
	void __priority(u32 priority) { data_._priority = priority; }


private:
	TextBox* txtbox_;
	D3DXVECTOR2 position_;
	DATA data_;

};

#endif	// _GIMMICK_CHECK_POINT_H_

//---------------------------------- EOF --------------------------------------
