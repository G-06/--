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
	:xaudio2_(nullptr)
	,mastering_voice_(nullptr)
	,volume_(1.0f)
{
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
// create xaudio2 sound
//=============================================================================
XAudio2Sound* XAudio2::CreateXAudio2Sound(void)
{
	XAudio2Sound* xaudio2_sound = new XAudio2Sound(xaudio2_);

	if(!SafeInitialize(xaudio2_sound))
	{
		SafeRelease(xaudio2_sound);
	}

	return xaudio2_sound;
}
//=============================================================================
// set master volume
//=============================================================================
void XAudio2::SetMasterVolume(const f32& volume)
{
	volume_ = volume;
	if(volume_ < 0.0f)
	{
		volume_ = 0.0f;
	}
	mastering_voice_->SetVolume(volume_);
}

//---------------------------------- EOF --------------------------------------
