//*****************************************************************************
//
// bgm
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _BGM_H_
#define _BGM_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"
#include "../resources/resource.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class XAudio2Sound;

//*****************************************************************************
// class definition
//*****************************************************************************
class BGM : public Basic
{
public:
	enum BGM_ID
	{
		BGM_ID_NONE = -1,

		BGM_ID_TITLE = BGM_TITLE,
		BGM_ID_TUTORIAL,
		BGM_ID_CREDIT,
		BGM_ID_STAGE_SELECT,
		BGM_ID_STAGE_01,
		BGM_ID_STAGE_02,
		BGM_ID_STAGE_03,
		BGM_ID_STAGE_04,
		BGM_ID_STAGE_05,
		BGM_ID_STAGE_06,
		BGM_ID_STAGE_07,
		BGM_ID_STAGE_08,
		BGM_ID_STAGE_09,
		BGM_ID_MAX,
	};

	// constructor
	BGM(IXAudio2* ixaudio2);

	// destructor
	virtual ~BGM(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// play
	bool Play(const BGM_ID& bgm_id);

	// stop
	void Stop(void);

	// set volume
	void SetVolume(const f32& volume);

	// accessor
	const BGM_ID& __current_bgm(void)const{ return current_bgm_; }
	void __is_loop(const bool& is_loop) { is_loop_ = is_loop; }
	void __is_fade(const bool& is_fade) { is_fade_ = is_fade; }
	void __fade_frame(const u32& fade_frame) { fade_frame_ = fade_frame; }
	const f32& __volume(void) { return volume_; }

private:
	IXAudio2* ixaudio2_;
	BGM_ID current_bgm_;
	BGM_ID preview_bgm_;
	bool is_loop_;
	bool is_fade_;
	u32 fade_frame_;
	u32 frame_count_;
	f32 volume_;
	XAudio2Sound* xaudio2_sound_[BGM_ID_MAX - BGM_ID_TITLE];
};

#endif // _BGM_H_

//---------------------------------- EOF --------------------------------------
