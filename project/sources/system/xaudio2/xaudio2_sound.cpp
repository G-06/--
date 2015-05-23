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
	,data_(nullptr)
	,size_(0)
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

	SafeDeleteArray(data_);

}

//=============================================================================
// load from file
//=============================================================================
bool XAudio2Sound::LoadFromFile(const s8* filename)
{
	HANDLE hFile;
	DWORD dwChunkSize = 0;
	DWORD dwChunkPosition = 0;
	DWORD dwFiletype;
	WAVEFORMATEXTENSIBLE wfx;
	XAUDIO2_BUFFER buffer;

	// バッファのクリア
	memset(&wfx,0,sizeof(WAVEFORMATEXTENSIBLE));
	memset(&buffer,0,sizeof(XAUDIO2_BUFFER));

	// サウンドデータファイルの生成
	hFile = CreateFile(filename,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,NULL);

	if(hFile == INVALID_HANDLE_VALUE)
	{
		//MessageBox(hWnd,"サウンドデータファイルの生成に失敗！(1)","警告！",MB_ICONWARNING);
		return (HRESULT_FROM_WIN32(GetLastError()) == S_OK);
	}

	if(SetFilePointer(hFile,0,NULL,FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動
		//MessageBox(hWnd,"サウンドデータファイルの生成に失敗！(2)","警告！",MB_ICONWARNING);
		return (HRESULT_FROM_WIN32(GetLastError()) == S_OK);
	}

	// WAVEファイルのチェック
	if(FAILED(CheckChunk(hFile,'FFIR',&dwChunkSize,&dwChunkPosition)))
	{
		//MessageBox(hWnd,"WAVEファイルのチェックに失敗！(1)","警告！",MB_ICONWARNING);
		return false;
	}

	if(FAILED(ReadChunkData(hFile,&dwFiletype,sizeof(DWORD),dwChunkPosition)))
	{
		//MessageBox(hWnd,"WAVEファイルのチェックに失敗！(2)","警告！",MB_ICONWARNING);
		return false;
	}

	if(dwFiletype != 'EVAW')
	{
		//MessageBox(hWnd,"WAVEファイルのチェックに失敗！(3)","警告！",MB_ICONWARNING);
		return false;
	}

	// フォーマットチェック
	if(FAILED(CheckChunk(hFile,' tmf',&dwChunkSize,&dwChunkPosition)))
	{
		//MessageBox(hWnd,"フォーマットチェックに失敗！(1)","警告！",MB_ICONWARNING);
		return false;
	}

	if(FAILED(ReadChunkData(hFile,&wfx,dwChunkSize,dwChunkPosition)))
	{
		//MessageBox(hWnd,"フォーマットチェックに失敗！(2)","警告！",MB_ICONWARNING);
		return false;
	}

	// オーディオデータ読み込み
	if(FAILED(CheckChunk(hFile,'atad',&size_,&dwChunkPosition)))
	{
		//MessageBox(hWnd,"オーディオデータ読み込みに失敗！(1)","警告！",MB_ICONWARNING);
		return false;
	}

	data_ = new u8[size_];

	if(FAILED(ReadChunkData(hFile,data_,size_,dwChunkPosition)))
	{
		//MessageBox(hWnd,"オーディオデータ読み込みに失敗！(2)","警告！",MB_ICONWARNING);
		return false;
	}

	// ソースボイスの生成
	if(FAILED(ixaudio2_->CreateSourceVoice(&ixaudio2_source_voice_,&(wfx.Format))))
	{
		//MessageBox(hWnd,"ソースボイスの生成に失敗！","警告！",MB_ICONWARNING);
		return false;
	}

	memset(&buffer,0,sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = size_;
	buffer.pAudioData = data_;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = 0;

	// オーディオバッファの登録
	ixaudio2_source_voice_->SubmitSourceBuffer(&buffer);

	return true;
}

//=============================================================================
// play
//=============================================================================
bool XAudio2Sound::Play(const u32& loop_count)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	ixaudio2_source_voice_->SetVolume(volume_);

	if(!is_play_)
	{
		memset(&buffer,0,sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = size_;
		buffer.pAudioData = data_;
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
// チャンクのチェック
//=============================================================================
HRESULT XAudio2Sound::CheckChunk(HANDLE hFile,DWORD format,DWORD *pChunkSize,DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;

	if(SetFilePointer(hFile,0,NULL,FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while(hr == S_OK)
	{
		if(ReadFile(hFile,&dwChunkType,sizeof(DWORD),&dwRead,NULL) == 0)
		{// チャンクの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if(ReadFile(hFile,&dwChunkDataSize,sizeof(DWORD),&dwRead,NULL) == 0)
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch(dwChunkType)
		{
			case 'FFIR':
				dwRIFFDataSize = dwChunkDataSize;
				dwChunkDataSize = 4;
				if(ReadFile(hFile,&dwFileType,sizeof(DWORD),&dwRead,NULL) == 0)
				{// ファイルタイプの読み込み
					hr = HRESULT_FROM_WIN32(GetLastError());
				}
				break;

			default:
				if(SetFilePointer(hFile,dwChunkDataSize,NULL,FILE_CURRENT) == INVALID_SET_FILE_POINTER)
				{// ファイルポインタをチャンクデータ分移動
					return HRESULT_FROM_WIN32(GetLastError());
				}
		}

		dwOffset += sizeof(DWORD) * 2;
		if(dwChunkType == format)
		{
			*pChunkSize = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if(dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}

	return S_OK;
}

//=============================================================================
// チャンクデータの読み込み
//=============================================================================
HRESULT XAudio2Sound::ReadChunkData(HANDLE hFile,void *pBuffer,DWORD dwBuffersize,DWORD dwBufferoffset)
{
	DWORD dwRead;

	if(SetFilePointer(hFile,dwBufferoffset,NULL,FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if(ReadFile(hFile,pBuffer,dwBuffersize,&dwRead,NULL) == 0)
	{// データの読み込み
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}

//---------------------------------- EOF --------------------------------------
