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

	// create xaudio2 sound
	XAudio2Sound* CreateXAudio2Sound(void);

	// set master volume
	void SetMasterVolume(const f32& volume);

	// accessor
	const f32& __volume(void) { return volume_; }

private:
	IXAudio2* xaudio2_;
	IXAudio2MasteringVoice* mastering_voice_;
	f32 volume_;

};

#endif // _XAUDIO2_H_

//---------------------------------- EOF --------------------------------------
