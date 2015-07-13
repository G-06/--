//*****************************************************************************
//
// se
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _SE_H_
#define _SE_H_

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
class SE : public Basic
{
public:
	enum SE_ID
	{
		SE_ID_NONE = -1,
		SE_ID_DECIDE = SE_DECIDE,
		SE_ID_CANCEL,
		SE_ID_CURSOR,
		SE_ID_WINDOW_OPEN,
		SE_ID_WINDOW_CLOSE,
		SE_ID_WINDOW_SELECT,
		SE_ID_NYAS_JUMP,
		SE_ID_NYAS_LIGHT_END,
		SE_ID_NYAS_LIGHT_START,
		SE_ID_NYAS_LIGHT_COLLISION,
		SE_ID_REFLECTION,
		SE_ID_DEATH,
		SE_ID_CHECK_POINT,
		SE_ID_NEW_RECORD,
		SE_ID_GOAL,
		SE_ID_STAGE_START,
		SE_ID_PAUSE,
		SE_ID_MAX,
	};

	// constructor
	SE(IXAudio2* ixaudio2);

	// destructor
	virtual ~SE(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// play
	bool Play(const SE_ID& se_id);

	// stop
	void Stop(void);

	// set volume
	void SetVolume(const f32& volume);

	// accessor
	const f32& __volume(void) { return volume_; }

private:
	static const u32 SE_MAX = 10;

	IXAudio2* ixaudio2_;
	f32 volume_;
	XAudio2Sound* xaudio2_sound_[SE_ID_MAX - SE_ID_DECIDE];
	IXAudio2SourceVoice* ixaudio2_source_voices_[SE_MAX];
	bool is_use_[SE_MAX];
	XAUDIO2_BUFFER xaudio2_buffers_[SE_MAX];

};

#endif // _SE_H_

//---------------------------------- EOF --------------------------------------
