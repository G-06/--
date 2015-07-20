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
		ixaudio2_source_voices_[i] = nullptr;
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
	for(u32 i = SE_ID_DECIDE;i < SE_ID_MAX;++i)
	{
		xaudio2_sound_[i - SE_ID_DECIDE] = new XAudio2Sound(ixaudio2_);

		if(!SafeInitialize(xaudio2_sound_[i - SE_ID_DECIDE]))
		{
			SafeRelease(xaudio2_sound_[i - SE_ID_DECIDE]);
			return false;
		}

		xaudio2_sound_[i - SE_ID_DECIDE]->LoadFromResource(MAKEINTRESOURCE(i));
	}

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void SE::Uninitialize(void)
{
	for(u32 i = SE_ID_DECIDE;i < SE_ID_MAX;++i)
	{
		if(ixaudio2_source_voices_[i - SE_ID_DECIDE] != nullptr)
		{
			is_use_[i - SE_ID_DECIDE] = false;
			ixaudio2_source_voices_[i - SE_ID_DECIDE]->Stop();
			ixaudio2_source_voices_[i - SE_ID_DECIDE]->DestroyVoice();
			ixaudio2_source_voices_[i - SE_ID_DECIDE] = nullptr;
		}
		SafeRelease(xaudio2_sound_[i - SE_ID_DECIDE]);
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

	ixaudio2_source_voices_[number] = xaudio2_sound_[se_id - SE_ID_DECIDE]->CreateCloneIXAudio2SourceVoice();
	xaudio2_sound_[se_id - SE_ID_DECIDE]->CloneXAudio2Buffer(&xaudio2_buffers_[number]);
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
