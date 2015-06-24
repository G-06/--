//*****************************************************************************
//
// �`���[�g���A���q�[
//
// Author	: kitazawa taichi
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _TUTORIAL_BACK_H_
#define _TUTORIAL_BACK_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"
#include "system/directx9/texture/texture.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class MessageSpriteSmooth;

//*****************************************************************************
// class definition
//*****************************************************************************
class TutorialBack : public Basic
{
public:
	// constructor
	TutorialBack(void);

	// destructor
	virtual ~TutorialBack(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// ���b�Z�[�W�̎��
	enum MESSAGE{
		MESSAGE_YES = 0,
		MESSAGE_NO,
		MESSAGE_MAX
	};

	// show close
	// �ǂ������ɊJ��
	void Show(void);
	void Close(void);

	const bool& __is_show(void) {return is_show_;}
	void __dest_frame_count(const u32& frame){dest_frame_count_ = frame;}
	const bool& __is_move(void) {return is_move_;}

	void __window_position(const D3DXVECTOR2& position){window_position_ = position;}
	void __window_size(const D3DXVECTOR2& size){window_size_ = size;}

private:

	static const D3DXVECTOR2 DEFAULT_POSITION;
	static const D3DXVECTOR2 DEFAULT_SIZE;
	static const u32 SELECT_MAX = MESSAGE_MAX;

	// �ؑւ��p
	void _ChangeSelect(const s32& now, const s32& old);

	MessageSpriteSmooth* window_;

	// �K��ʒu
	D3DXVECTOR2 window_position_;

	// �ړ�����܂ł̃J�E���g
	u32 dest_frame_count_;


	// �J���Ă���H
	bool is_show_;

	// �����Ă�H
	bool is_move_;

	// size
	D3DXVECTOR2 window_size_;
};

#endif	// _MESSAGE_WINDOW_H_

//---------------------------------- EOF --------------------------------------
