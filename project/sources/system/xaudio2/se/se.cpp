//*****************************************************************************
//
// se
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "se.h"
#include "../xaudio2_sound.h"

//=============================================================================
// constructor
//=============================================================================
SE::SE(IXAudio2* ixaudio2)
	:ixaudio2_(ixaudio2)
	,volume_(1.0f)
{
	for(u32 i = 0;i < SE_MAX;++i)
	{
		is_use_[i] = false;
	}
}

//=============================================================================
// destructor
//=============================================================================
SE::~SE(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool SE::Initialize(void)
{
	for(u32 i = SE_ID_TEST;i < SE_ID_MAX;++i)
	{
		xaudio2_sound_[i - SE_ID_TEST] = new XAudio2Sound(ixaudio2_);

		if(!SafeInitialize(xaudio2_sound_[i - SE_ID_TEST]))
		{
			SafeRelease(xaudio2_sound_[i - SE_ID_TEST]);
			return false;
		}

		xaudio2_sound_[i - SE_ID_TEST]->LoadFromResource(MAKEINTRESOURCE(i));
	}

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void SE::Uninitialize(void)
{
	for(u32 i = SE_ID_TEST;i < SE_ID_MAX;++i)
	{
		SafeRelease(xaudio2_sound_[i - SE_ID_TEST]);
	}
}

//=============================================================================
// update
//=============================================================================
void SE::Update(void)
{
	XAUDIO2_VOICE_STATE xaudio2_voice_state;

	for(u32 i = 0;i < SE_MAX;++i)
	{
		if(is_use_[i])
		{
			ixaudio2_source_voices_[i]->GetState(&xaudio2_voice_state);

			if(xaudio2_voice_state.BuffersQueued == 0)
			{
				is_use_[i] = false;
				if(ixaudio2_source_voices_[i] != nullptr)
				{
					ixaudio2_source_voices_[i]->Stop();
					ixaudio2_source_voices_[i]->DestroyVoice();
					ixaudio2_source_voices_[i] = nullptr;
				}
			}
		}
	}
}

//=============================================================================
// play
//=============================================================================
bool SE::Play(const SE_ID& se_id)
{
	u32 number = SE_MAX;
	for(u32 i = 0;i < SE_MAX;++i)
	{
		if(!is_use_[i])
		{
			number = i;
			break;
		}
	}
	if(number >= SE_MAX)
	{
		return false;
	}

	ixaudio2_source_voices_[number] = xaudio2_sound_[se_id - SE_ID_TEST]->CreateCloneIXAudio2SourceVoice();
	xaudio2_sound_[se_id - SE_ID_TEST]->CloneXAudio2Buffer(&xaudio2_buffers_[number]);
	ixaudio2_source_voices_[number]->SetVolume(volume_);
	ixaudio2_source_voices_[number]->SubmitSourceBuffer(&xaudio2_buffers_[number]);
	ixaudio2_source_voices_[number]->Start(0);
	is_use_[number] = true;

	return true;
}

//=============================================================================
// stop
//=============================================================================
void SE::Stop(void)
{
}

//=============================================================================
// set volume
//=============================================================================
void SE::SetVolume(const f32& volume)
{
	volume_ = volume;

	if(volume_ < 0.0f)
	{
		volume_ = 0.0f;
	}
	for(u32 i = 0;i < SE_MAX;++i)
	{
		if(is_use_[i])
		{
			ixaudio2_source_voices_[i]->SetVolume(volume_);
		}
	}
}

//---------------------------------- EOF --------------------------------------
