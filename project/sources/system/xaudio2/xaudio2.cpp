//*****************************************************************************
//
// xaudio2
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "xaudio2.h"

//=============================================================================
// constructor
//=============================================================================
XAudio2::XAudio2(void)
{
	xaudio2_ = nullptr;
	mastering_voice_ = nullptr;
}

//=============================================================================
// destructor
//=============================================================================
XAudio2::~XAudio2(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool XAudio2::Initialize(void)
{
	// initiialize COM
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// create xaudio2
	if(FAILED(XAudio2Create(&xaudio2_,0)))
	{
		CoUninitialize();
		return false;
	}

	// create master voice
	if(FAILED(xaudio2_->CreateMasteringVoice(&mastering_voice_)))
	{
		SafeRelease(xaudio2_);
		CoUninitialize();
		return false;
	}

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void XAudio2::Uninitialize(void)
{
	if(mastering_voice_ != nullptr)
	{
		mastering_voice_->DestroyVoice();
		mastering_voice_ = nullptr;
	}

	SafeRelease(xaudio2_);

	CoUninitialize();
}

//=============================================================================
// load wave file
//=============================================================================
bool LoadWaveFile(const s8* filename)
{
	return true;
}

//=============================================================================
// チャンクのチェック
//=============================================================================
HRESULT XAudio2::CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;
	
	if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	while(hr == S_OK)
	{
		if(ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if(ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch(dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize  = dwChunkDataSize;
			dwChunkDataSize = 4;
			if(ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// ファイルタイプの読み込み
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if(SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタをチャンクデータ分移動
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if(dwChunkType == format)
		{
			*pChunkSize         = dwChunkDataSize;
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
HRESULT XAudio2::ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;
	
	if(SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if(ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// データの読み込み
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	return S_OK;
}


//---------------------------------- EOF --------------------------------------
