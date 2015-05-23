//*****************************************************************************
//
// xaudio2 sound
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _XAUDIO2_SOUND_H_
#define _XAUDIO2_SOUND_H_

//*****************************************************************************
// include
//*****************************************************************************

//*****************************************************************************
// forward declaration
//*****************************************************************************

//*****************************************************************************
// class definition
//*****************************************************************************
class XAudio2Sound : public Basic
{
public:
	// constructor
	XAudio2Sound(IXAudio2* ixaudio2);

	// destructor
	virtual ~XAudio2Sound(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// load from file
	bool LoadFromFile(const s8* filename);

	// play
	bool Play(const u32& loop_count);

	// stop
	void Stop(void);

	// pause
	void Pause(void);

	// set volume
	void SetVolume(const f32& volume);

	// accesor
	const f32& __volume(void) { return volume_; }
private:
	IXAudio2* ixaudio2_;
	IXAudio2SourceVoice* ixaudio2_source_voice_;
	u8* data_;
	u64 size_;
	bool is_pause_;
	bool is_play_;
	f32 volume_;

	HRESULT CheckChunk(HANDLE hFile,DWORD format,DWORD *pChunkSize,DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile,void *pBuffer,DWORD dwBuffersize,DWORD dwBufferoffset);

};

#endif // _XAUDIO2_SOUND_H_

//---------------------------------- EOF --------------------------------------
