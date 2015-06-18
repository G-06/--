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
		SE_ID_TEST = SE_TEST,
		SE_ID_TEST2,
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
	XAudio2Sound* xaudio2_sound_[SE_ID_MAX - SE_ID_TEST];
	IXAudio2SourceVoice* ixaudio2_source_voices_[SE_MAX];
	bool is_use_[SE_MAX];
	XAUDIO2_BUFFER xaudio2_buffers_[SE_MAX];

};

#endif // _SE_H_

//---------------------------------- EOF --------------------------------------
