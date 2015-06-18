//*****************************************************************************
//
// xaudio2
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _XAUDIO2_H_
#define _XAUDIO2_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"
#include "xaudio2_sound.h"
#include "bgm/bgm.h"
#include "se/se.h"

//*****************************************************************************
// class definition
//*****************************************************************************
class XAudio2 : public Basic
{
public:
	// constructor
	XAudio2(void);

	// destructor
	virtual ~XAudio2(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// set volume
	void SetVolume(const f32& volume);

	// accessor
	const f32& __volume(void) { return volume_; }
	BGM* __bgm(void)const { return bgm_; }
	SE* __se(void)const { return se_; }
private:
	IXAudio2* ixaudio2_;
	IXAudio2MasteringVoice* ixaudio2_mastering_voice_;
	f32 volume_;
	BGM* bgm_;
	SE* se_;
};

#endif // _XAUDIO2_H_

//---------------------------------- EOF --------------------------------------
