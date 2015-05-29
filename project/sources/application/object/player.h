//*****************************************************************************
//
// player
//
// Author		: Ryotaro Arai
//				: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"
#include "common/animation/animation.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Sprite;

//*****************************************************************************
// class definition
//*****************************************************************************
class Player : public Basic
{
public:
	enum COLLISION_MODE
	{
		COLLISION_DOWN = 0,
		COLLISION_RIGHT,
		COLLISION_LEFT,
		COLLISION_MAX
	};

	// constructor
	Player(void);

	// destructor
	virtual ~Player(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// move
	void Move(f32 vector);

	// jump
	void Jump(void);

	// hit stage
	void HitStage(const D3DXVECTOR2& position,bool is_floor = false);

	// change light mode
	void ChangeLightMode(const D3DXVECTOR2& vector);

	// stop light mode
	void StopLightMode(void);

	// change direction
	void ChangeDirection(const D3DXVECTOR2& vector);

	// ���W�̎擾
	const D3DXVECTOR2& __position(void)const{ return position_; }

	void __position(const D3DXVECTOR2& position){ position_ = position; }

	// �O����W�̎擾
	const D3DXVECTOR2& __old_position(void)const{ return old_position_; }

	// �I�t�Z�b�g���W�̐ݒ�
	void __offset_position(const D3DXVECTOR2& offset){ offset_position_ = offset; }

	// �T�C�Y�擾
	const D3DXVECTOR2& __size(void)const{ return size_; }

private:
	void LightMode(bool is_light, bool is_right);

	enum ANIMATION_TYPE
	{
		ANIMATION_TYPE_WAIT = 0,
		ANIMATION_TYPE_RUN,
		ANIMATION_TYPE_LIGHT,
		ANIMATION_TYPE_MAX
	};

	struct ANIMATION_TEXTURE_DATA
	{
		u32 _texture_id;
		u16 _division_width;
		u16 _division_height;

		ANIMATION_TEXTURE_DATA(u32 texture_id,u16 division_width,u16 division_height)
			:_texture_id(texture_id)
			,_division_width(division_width)
			,_division_height(division_height)
		{}
	};

	static const Animation::DATA ANIMATION_DATA[];
	static const u32 ANIMATION_RUN_START;
	static const u32 ANIMATION_WAIT_START;
	static const u32 ANIMATION_LIGHT_START;
	static const f32 LIGHT_SPEED;
	static const f32 SPEED;
	static const f32 DECREMENT;
	static const f32 JUMP_SPEED;
	static const ANIMATION_TEXTURE_DATA TEXTURE_DATA[ANIMATION_TYPE_MAX];

	D3DXVECTOR2 position_;				// �v���C���[���W
	D3DXVECTOR2 old_position_;			// �v���C���[�̑O����W
	D3DXVECTOR2 move_;					// �v���C���[�̈ړ���
	D3DXVECTOR2 size_;					// �v���C���[�T�C�Y
	D3DXVECTOR2 offset_position_;		// �I�t�Z�b�g���W
	u32			acceleration_counter_;	// �����J�E���^�[
	u32			slowdown_counter_;		// �����J�E���^�[
	bool		is_left_;				// �v���C���[�̌���
	bool		is_light_;				// �����t���O
	bool		is_fly_;				// �󒆃t���O
	bool		is_enable_light_;
	Sprite*		player_;				// �v���C���[�X�v���C�g
	Animation*	animation_;
	ANIMATION_TYPE animation_type_;
};

#endif	// _PLAYER_H_

//---------------------------------- EOF --------------------------------------
