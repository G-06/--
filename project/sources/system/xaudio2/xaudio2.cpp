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
	,se_(nullptr)
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
		Uninitialize();
		return false;
	}

	// create master voice
	if(FAILED(ixaudio2_->CreateMasteringVoice(&ixaudio2_mastering_voice_)))
	{
		Uninitialize();
		return false;
	}

	bgm_ = new BGM(ixaudio2_);

	if(!SafeInitialize(bgm_))
	{
		Uninitialize();
		return false;
	}

	se_ = new SE(ixaudio2_);

	if(!SafeInitialize(se_))
	{
		Uninitialize();
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
	SafeRelease(se_);
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
	se_->Update();
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
