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
class MessageWindow;
class TutorialBack;

//*****************************************************************************
// class definition
//*****************************************************************************
class GimmickTutorialText : public Gimmick
{
public:
	enum MASSAGE_TYPE
	{
		MASSAGE_TYPE_MOVE=0,
		MASSAGE_TYPE_JUMP,
		MASSAGE_TYPE_LIGHT,
		MASSAGE_TYPE_GIMMICK_GLAS,
		MASSAGE_TYPE_GIMMICK_MIRROR,
		MASSAGE_TYPE_MAX

	};

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
	void __type(u32 type){type_ = (MASSAGE_TYPE)type;};

private:
	TextBox* txtbox_;
	D3DXVECTOR2 position_;
	DATA data_;

	MASSAGE_TYPE type_;

	TutorialBack* back_;
	bool back_flag_;

	u32 wait_;

};

#endif	// _GIMMICK_CHECK_POINT_H_

//---------------------------------- EOF --------------------------------------
