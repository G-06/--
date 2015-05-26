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
	:ixaudio2_(nullptr)
	,ixaudio2_mastering_voice_(nullptr)
	,volume_(1.0f)
	,bgm_(nullptr)
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
	if(FAILED(XAudio2Create(&ixaudio2_,0)))
	{
		CoUninitialize();
		return false;
	}

	// create master voice
	if(FAILED(ixaudio2_->CreateMasteringVoice(&ixaudio2_mastering_voice_)))
	{
		SafeRelease(ixaudio2_);
		CoUninitialize();
		return false;
	}

	bgm_ = new BGM(ixaudio2_);

	if(!SafeInitialize(bgm_))
	{
		if(ixaudio2_mastering_voice_ != nullptr)
		{
			ixaudio2_mastering_voice_->DestroyVoice();
			ixaudio2_mastering_voice_ = nullptr;
		}
		SafeRelease(ixaudio2_);
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
	SafeRelease(bgm_);

	if(ixaudio2_mastering_voice_ != nullptr)
	{
		ixaudio2_mastering_voice_->DestroyVoice();
		ixaudio2_mastering_voice_ = nullptr;
	}

	SafeRelease(ixaudio2_);

	CoUninitialize();
}

//=============================================================================
// update
//=============================================================================
void XAudio2::Update(void)
{
	bgm_->Update();
}

//=============================================================================
// set volume
//=============================================================================
void XAudio2::SetVolume(const f32& volume)
{
	volume_ = volume;

	if(volume_ < 0.0f)
	{
		volume_ = 0.0f;
	}

	ixaudio2_mastering_voice_->SetVolume(volume_);
}

//---------------------------------- EOF --------------------------------------
