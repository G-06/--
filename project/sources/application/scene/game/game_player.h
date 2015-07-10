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
class EffectDead;
class EffectLightning;
class EffectLocus;

//*****************************************************************************
// class definition
//*****************************************************************************
class GamePlayer : public Basic
{
public:
	enum CAT_STATUS
	{
		CAT_STATUS_LIVE = 0,	//生きてる　ゲーム遊べる
		CAT_STATUS_DEAD,		//死んだ　チェックポイントから復活
		CAT_STATUS_CLEAR,		//クリア
		CAT_STATUS_WARP,		//ワープ
		CAT_STATUS_MAX
	};

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

	// heal
	void GamePlayer::Heal(u32 health);

	// clear
	void Clear(void);

	//ワープするぜ
	void Warp(void);

	// 座標の取得
	const D3DXVECTOR2& __position(void)const{ return position_; }

	void __position(const D3DXVECTOR2& position){ position_ = position; }

	// 前回座標の取得
	const D3DXVECTOR2& __old_position(void)const{ return old_position_; }

	// オフセット座標の設定
	void __offset_position(const D3DXVECTOR2& offset){ offset_position_ = offset; }

	// サイズ取得
	const D3DXVECTOR2& __size(void)const{ return size_; }

	const D3DXVECTOR2& __move(void)const { return move_; }
	void __return_position(const D3DXVECTOR2& return_position) { return_position_ = return_position; }

	s32 __sp(void)const { return sp_; }
	s32 __sp_max(void)const { return sp_max_; }
	s32 __sp_recover_speed(void)const { return sp_recover_speed_; }
	void __sp_recover_speed(s32 sp_recover_speed) { sp_recover_speed_ = sp_recover_speed; }
	s32 __life(void)const { return life_; }
	u32 __check_point_priority(void) { return check_point_priority_; }
	void __check_point_priority(u32 check_point_priority) { check_point_priority_ = check_point_priority; }
	bool __is_light(void) { return is_light_; }
	bool __is_preview_light(void) { return is_preview_light_; }
	bool __is_force_light(void) { return is_force_light_; }
	void __is_force_light(bool is_force_light) { is_force_light_ = is_force_light; }
	void __is_sp_recover_speed_up(bool is_sp_recover_speed_up) { is_sp_recover_speed_up_ = is_sp_recover_speed_up; }
	void __is_sp_down(bool is_sp_down) { is_sp_down_ = is_sp_down; }


	u32 __Get_status(void){return (u32)Status_;}
	void __Set_status(u32 status){ Status_ = (CAT_STATUS)status;}
	bool __Get_warpout(void){return warp_out_;}

	static const u32 DEAD_TIME;
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
	static const s32 DEFAULT_SP_RECOVER_SPEED;
	static const D3DXVECTOR2 DEFAULT_SIZE;
	static const u32 OUT_WABISABI;	//ワープして消えた後の余韻

	D3DXVECTOR2 position_;				// プレイヤー座標
	D3DXVECTOR2 old_position_;			// プレイヤーの前回座標
	D3DXVECTOR2 move_;					// プレイヤーの移動量
	D3DXVECTOR2 size_;					// プレイヤーサイズ
	D3DXVECTOR2 offset_position_;		// オフセット座標
	bool		is_left_;				// プレイヤーの向き
	bool		is_light_;				// 光化フラグ
	bool		is_fly_;				// 空中フラグ
	bool		is_enable_light_;
	s32 life_;
	s32 sp_;
	s32 sp_max_;
	s32 sp_recover_speed_;
	bool is_sp_recover_speed_up_;
	bool is_sp_down_;
	D3DXVECTOR2 return_position_;
	u32 check_point_priority_;
	D3DXVECTOR2 acceleration_;
	ObjectPlayer*		player_;				// プレイヤースプライト
	EffectLightning* lightning_start_;
	EffectDead* nyas_dead_;
	EffectLocus* nyas_locus_[100];
	bool is_preview_light_;
	bool is_force_light_;

	CAT_STATUS Status_;		//プレイヤーの状態

	void UpdateLive(void);		//生きてるときの更新
	void UpdateDead(void);		//死んでるときの更新
	void UpdateClear(void);		//クリアした時の更新
	void UpdateWarp(void);		//ワープしてるときの更新
	u32 dead_cnt_;				//死んだときのアニメーションカウント
	u32 warp_cnt_;				//ワープするときのアニメーション

	bool warp_out_;
};

#endif	// _PLAYER_H_

//---------------------------------- EOF --------------------------------------
