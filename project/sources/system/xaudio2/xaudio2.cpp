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
	// initiialize
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
XAudio2Sound* XAudio2::LoadWaveFile(const s8* filename)
{
	XAudio2Sound* xaudio2_sound = new XAudio2Sound(xaudio2_);

	xaudio2_sound->Initialize();

	xaudio2_sound->LoadFromFile(filename);

	return xaudio2_sound;
}

//---------------------------------- EOF --------------------------------------
