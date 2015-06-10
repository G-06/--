//*****************************************************************************
//
// message_sprite_smooth
//
// Author	: masato masuda
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _MESSAGE_SPRITE_SMOOTH_H_
#define _MESSAGE_SPRITE_SMOOTH_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"
#include "system/directx9/texture/texture.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Sprite;

//*****************************************************************************
// class definition
//*****************************************************************************
class MessageSpriteSmooth : public Basic
{
public:
	// constructor
	MessageSpriteSmooth(void);

	// destructor
	virtual ~MessageSpriteSmooth(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	inline void __dest_position(const D3DXVECTOR2& position){dest_position_ = position;}
	inline void __dest_size(const D3DXVECTOR2& size){dest_size_ = size;}
	inline void __dest_color(const D3DXCOLOR& color){dest_color_ = color;}
	inline void __dest_frame(u32 frame){dest_frame_ = frame;}

	// accessor
	const D3DXVECTOR2& __position(void)const;
	void __position(const D3DXVECTOR2& position);
	const D3DXVECTOR2& __size(void)const;
	void __size(const D3DXVECTOR2& size);
	void __color(const D3DXCOLOR& color);
	const bool& __move_flag_(void){return move_flag_;}
	void __texture_id(const Texture::TEXTURE_ID& texture_id);

	// �ړ��J�n
	void StartMove(void);

	// ���݂̐ݒ�Ɠ���
	void SynchroParameter(void);

	// �ړI�̐ݒ�Ƌ�������
	void ForcingDest(void);

private:
	static const D3DXVECTOR2 DEFAULT_POSITION;
	static const D3DXVECTOR2 DEFAULT_SIZE;

	// �ړI(pos, size, color)
	D3DXVECTOR2	dest_position_;
	D3DXVECTOR2	dest_size_;
	D3DXCOLOR	dest_color_;

	D3DXVECTOR2	target_position_;
	D3DXVECTOR2	target_size_;
	D3DXCOLOR	target_color_;

	D3DXVECTOR2	old_position_;
	D3DXVECTOR2	old_size_;
	D3DXCOLOR	old_color_;

	// �ړI�܂ł̃t���[����
	u32 dest_frame_;

	// ���݂̃t���[����
	u32 now_frame_;

	// �ړ��t���O
	bool move_flag_;

	Sprite* sprite_;
};

#endif	// _MESSAGE_SPRITE_SMOOTH_H_

//---------------------------------- EOF --------------------------------------
