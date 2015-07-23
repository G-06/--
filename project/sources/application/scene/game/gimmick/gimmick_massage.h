//*****************************************************************************
//
// メッセージてきすと
//
// Author		: kitazawa taichi
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _GIMMICK_MASSAGE_H_
#define _GIMMICK_MASSAGE_H_

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
class GimmickMassage : public Gimmick
{
public:
	enum MASSAGE_TYPE
	{
		MASSAGE_TYPE_STAFF_TITLE=0,
		MASSAGE_TYPE_STAFF_MAKER,
		MASSAGE_TYPE_STAFF_LEADER,
		MASSAGE_TYPE_STAFF_DESIGNER,
		MASSAGE_TYPE_STAFF_PLANER_1,
		MASSAGE_TYPE_STAFF_PLANER_2,
		MASSAGE_TYPE_STAFF_PROGRAMMER_1,
		MASSAGE_TYPE_STAFF_PROGRAMMER_2,
		MASSAGE_TYPE_STAFF_PROGRAMMER_3,
		MASSAGE_TYPE_STAFF_PROGRAMMER_4,
		MASSAGE_TYPE_STAFF_SPECIAL_1,
		MASSAGE_TYPE_STAFF_SPECIAL_2,
		MASSAGE_TYPE_STAFF_SPECIAL_3,
		MASSAGE_TYPE_MAX

	};

	struct DATA
	{
		bool _is_hit;
	};

	// constructor
	GimmickMassage(void);

	// destructor
	virtual ~GimmickMassage(void);

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
	void __type(u32 type){type_ = (MASSAGE_TYPE)type;};
	//
	void __size(D3DXVECTOR2 size){size_ = size;}

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
