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

	// load wave file
	XAudio2Sound* LoadWaveFile(const s8* filename);

	// XAudio2�̎擾
	IXAudio2* __xaudio2(void){return xaudio2_;}

	// XAudio2�̎擾
	IXAudio2MasteringVoice* __mastering_voice(void){return mastering_voice_;}

private:
	IXAudio2* xaudio2_;
	IXAudio2MasteringVoice* mastering_voice_;
};

#endif // _XAUDIO2_H_

//---------------------------------- EOF --------------------------------------
