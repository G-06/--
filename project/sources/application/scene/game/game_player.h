//*****************************************************************************
//
// game player
//
// Author		: Ryotaro Arai
//				: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _GAME_PLAYER_H_
#define _GAME_PLAYER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"
#include "common/animation/animation.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class ObjectPlayer;

//*****************************************************************************
// class definition
//*****************************************************************************
class GamePlayer : public Basic
{
public:
	// constructor
	GamePlayer(void);

	// destructor
	virtual ~GamePlayer(void);

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

	// accelerate
	void Accelerate(const D3DXVECTOR2& acceleration);

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

	// dead
	void Dead(void);

	// clear
	void Clear(void);

	// ���W�̎擾
	const D3DXVECTOR2& __position(void)const{ return position_; }

	void __position(const D3DXVECTOR2& position){ position_ = position; }

	// �O����W�̎擾
	const D3DXVECTOR2& __old_position(void)const{ return old_position_; }

	// �I�t�Z�b�g���W�̐ݒ�
	void __offset_position(const D3DXVECTOR2& offset){ offset_position_ = offset; }

	// �T�C�Y�擾
	const D3DXVECTOR2& __size(void)const{ return size_; }

	const D3DXVECTOR2& __move(void)const { return move_; }
	void __return_position(const D3DXVECTOR2& return_position) { return_position_ = return_position; }

	s32 __sp(void)const { return sp_; }
	s32 __sp_max(void)const { return sp_max_; }
	s32 __life(void)const { return life_; }
	u32 __check_point_priority(void) { return check_point_priority_; }
	void __check_point_priority(u32 check_point_priority) { check_point_priority_ = check_point_priority; }

private:
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

	static const f32 LIGHT_SPEED;
	static const f32 SPEED;
	static const f32 DECREMENT;
	static const f32 JUMP_SPEED;
	static const s32 DEFAULT_LIFE_MAX;
	static const s32 DEFAULT_SP_MAX;

	D3DXVECTOR2 position_;				// �v���C���[���W
	D3DXVECTOR2 old_position_;			// �v���C���[�̑O����W
	D3DXVECTOR2 move_;					// �v���C���[�̈ړ���
	D3DXVECTOR2 size_;					// �v���C���[�T�C�Y
	D3DXVECTOR2 offset_position_;		// �I�t�Z�b�g���W
	bool		is_left_;				// �v���C���[�̌���
	bool		is_light_;				// �����t���O
	bool		is_fly_;				// �󒆃t���O
	bool		is_enable_light_;
	s32 life_;
	s32 sp_;
	s32 sp_max_;
	D3DXVECTOR2 return_position_;
	u32 check_point_priority_;
	D3DXVECTOR2 acceleration_;
	ObjectPlayer*		player_;				// �v���C���[�X�v���C�g

};

#endif	// _PLAYER_H_

//---------------------------------- EOF --------------------------------------
