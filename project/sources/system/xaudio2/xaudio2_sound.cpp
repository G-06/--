//*****************************************************************************
//
// xaudio2 sound
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "xaudio2_sound.h"

//=============================================================================
// constructor
//=============================================================================
XAudio2Sound::XAudio2Sound(IXAudio2* ixaudio2)
	:ixaudio2_(ixaudio2)
	,ixaudio2_source_voice_(nullptr)
	,is_play_(false)
	,is_pause_(false)
	,volume_(1.0f)
{
}

//=============================================================================
// destructor
//=============================================================================
XAudio2Sound::~XAudio2Sound(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool XAudio2Sound::Initialize(void)
{
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void XAudio2Sound::Uninitialize(void)
{
	if(ixaudio2_source_voice_ != nullptr)
	{
		ixaudio2_source_voice_->Stop();
		ixaudio2_source_voice_->DestroyVoice();
		ixaudio2_source_voice_ = nullptr;
	}

	SafeDeleteArray(xaudio2_buffer_.pAudioData);

}

//=============================================================================
// load from file
//=============================================================================
bool XAudio2Sound::LoadFromFile(const s8* filename)
{
	s8* data;
	FILE* file = nullptr;
	u32 size;

	fopen_s(&file,filename,"rb");

	if(file == nullptr)
	{
		return false;
	}

	// get file size
	fseek(file,0,SEEK_END);
	size = ftell(file);
	fseek(file,0,SEEK_SET);

	// read data
	data = new s8[size];
	fread(data,1,size,file);

	// close file
	fclose(file);

	// read wave data
	ReadWaveData(data);

	return true;
}

//=============================================================================
// play
//=============================================================================
bool XAudio2Sound::Play(const u32& loop_count)
{
	XAUDIO2_BUFFER buffer;

	ixaudio2_source_voice_->SetVolume(volume_);

	if(!is_play_)
	{
		memset(&buffer,0,sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = xaudio2_buffer_.AudioBytes;
		buffer.pAudioData = xaudio2_buffer_.pAudioData;
		buffer.Flags = XAUDIO2_END_OF_STREAM;

		if(loop_count == 0)
		{
			buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
		}
		else
		{
			buffer.LoopCount = loop_count - 1;
		}

		// オーディオバッファの登録
		ixaudio2_source_voice_->SubmitSourceBuffer(&buffer);

		// 再生
		ixaudio2_source_voice_->Start(0);
		is_play_ = true;
		is_pause_ = false;
	}

	return true;
}

//=============================================================================
// stop
//=============================================================================
void XAudio2Sound::Stop(void)
{
	if(is_play_)
	{
		ixaudio2_source_voice_->Stop(0);
		is_play_ = false;
		is_pause_ = true;
	}

	if(is_pause_)
	{
		ixaudio2_source_voice_->FlushSourceBuffers();
		is_pause_ = false;
	}
}

//=============================================================================
// pause
//=============================================================================
void XAudio2Sound::Pause(void)
{
	if(is_play_)
	{
		ixaudio2_source_voice_->Stop(0);
		is_play_ = false;
		is_pause_ = true;
	}
}

//=============================================================================
// set volume
//=============================================================================
void XAudio2Sound::SetVolume(const f32& volume)
{
	volume_ = volume;

	if(volume_ < 0.0f)
	{
		volume_ = 0.0f;
	}

	ixaudio2_source_voice_->SetVolume(volume_);
}

//=============================================================================
// create clone ixaudio2 source voice
//=============================================================================
IXAudio2SourceVoice* XAudio2Sound::CreateCloneIXAudio2SourceVoice(void)
{
	IXAudio2SourceVoice* ixaudio2_source_voice = nullptr;

	if(FAILED(ixaudio2_->CreateSourceVoice(&ixaudio2_source_voice,&waveformatex_)))
	{
		return nullptr;
	}

	return ixaudio2_source_voice;
}

//=============================================================================
// clone xaudio2 buffer
//=============================================================================
void XAudio2Sound::CloneXAudio2Buffer(XAUDIO2_BUFFER* xaudio2_buffer)
{
	memset(xaudio2_buffer,0,sizeof(XAUDIO2_BUFFER));
	xaudio2_buffer->AudioBytes = xaudio2_buffer_.AudioBytes;
	xaudio2_buffer->pAudioData = xaudio2_buffer_.pAudioData;
	xaudio2_buffer->Flags = XAUDIO2_END_OF_STREAM;
	xaudio2_buffer->LoopCount = 0;
}

//=============================================================================
// load from resource
//=============================================================================
bool XAudio2Sound::LoadFromResource(const s8* resource)
{
	HRSRC hrsrc = FindResource(GetModuleHandle(NULL),MAKEINTRESOURCE(resource),"WAVE");
	HGLOBAL hglobal = LoadResource(NULL,hrsrc);
	s8* data = (s8*)LockResource(hglobal);

	return ReadWaveData(data);
}

//=============================================================================
// read wave data
//=============================================================================
bool XAudio2Sound::ReadWaveData(const s8* data)
{
	struct RiffHeader
	{
		s8 riff[4];
		s32 size;
		u32 type;
	};

	struct FormatChunk
	{
		s8 id[4];
		s32 size;
		s16 format;
		u16 channels;
		u32 samplerate;
		u32 bytepersec;
		u16 blockalign;
		u16 bitswidth;
	};

	struct DataChunk
	{
		s8 id[4];
		s32 size;
	};

	XAUDIO2_BUFFER xaudio2_buffer;
	RiffHeader riff_header;
	FormatChunk format_chank;
	DataChunk data_chunk;
	u8* buffer = nullptr;
	u32 offset = 0;

	// read riff header
	memcpy(&riff_header,&data[0],sizeof(RiffHeader));

	// check RIFF
	if(riff_header.riff[0] != 'R' || riff_header.riff[1] != 'I' || riff_header.riff[2] != 'F' || riff_header.riff[3] != 'F')
	{
		return false;
	}

	// offset
	offset += sizeof(RiffHeader);

	// read format chunk
	memcpy(&format_chank,&data[offset],sizeof(FormatChunk));

	if(format_chank.id[0] != 'f' || format_chank.id[1] != 'm' || format_chank.id[2] != 't')
	{
		return false;
	}

	// offset
	offset += format_chank.size + 8;

	while(1)
	{
		// read data chunk
		memcpy(&data_chunk,&data[offset],sizeof(DataChunk));

		if(data_chunk.id[0] != 'd' || data_chunk.id[1] != 'a' || data_chunk.id[2] != 't' || data_chunk.id[3] != 'a')
		{
			offset += data_chunk.size + 8;
		}
		else
		{
			break;
		}
	}

	// offset
	offset += sizeof(DataChunk);

	// read data
	buffer = new u8[data_chunk.size];
	for(u32 i = 0;i < data_chunk.size;++i)
	{
		buffer[i] = data[i + offset];
	}

	xaudio2_buffer_.AudioBytes = data_chunk.size;
	xaudio2_buffer_.pAudioData = buffer;

	waveformatex_.wFormatTag = format_chank.format;
	waveformatex_.nChannels = format_chank.channels;
	waveformatex_.nSamplesPerSec = format_chank.samplerate;
	waveformatex_.nAvgBytesPerSec = format_chank.bytepersec;
	waveformatex_.nBlockAlign = format_chank.blockalign;
	waveformatex_.wBitsPerSample = format_chank.bitswidth;
	waveformatex_.cbSize = sizeof(FormatChunk) - format_chank.size - 8;

	// ソースボイスの生成
	if(FAILED(ixaudio2_->CreateSourceVoice(&ixaudio2_source_voice_,&waveformatex_)))
	{
		return false;
	}

	return true;
}

//---------------------------------- EOF --------------------------------------
