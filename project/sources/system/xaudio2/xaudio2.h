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

	// �`�����N�̃`�F�b�N
	HRESULT CheckChunk(HANDLE h_file, DWORD format, DWORD *chunk_size, DWORD *chunk_data_position);

	// �`�����N�f�[�^�̓ǂݍ���
	HRESULT ReadChunkData(HANDLE h_file, void* buffer, DWORD buffer_size, DWORD buffer_offset);

	// XAudio2�̎擾
	IXAudio2* xaudio2(void){return xaudio2_;}

	// XAudio2�̎擾
	IXAudio2MasteringVoice* mastering_voice(void){return mastering_voice_;}

private:
	IXAudio2* xaudio2_;
	IXAudio2MasteringVoice* mastering_voice_;
};

#endif // _XAUDIO2_H_

//---------------------------------- EOF --------------------------------------
