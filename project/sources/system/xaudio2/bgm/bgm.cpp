//*****************************************************************************
//
// bgm
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "bgm.h"
#include "../xaudio2_sound.h"

//=============================================================================
// constructor
//=============================================================================
BGM::BGM(IXAudio2* ixaudio2)
	:ixaudio2_(ixaudio2)
	,current_bgm_(BGM_ID_NONE)
	,preview_bgm_(BGM_ID_NONE)
	,is_loop_(true)
	,volume_(1.0f)
	,fade_frame_(60)
	,frame_count_(0)
	,is_fade_(true)
{
}

//=============================================================================
// destructor
//=============================================================================
BGM::~BGM(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool BGM::Initialize(void)
{
	for(u32 i = BGM_ID_TEST;i < BGM_ID_MAX;++i)
	{
		xaudio2_sound_[i - BGM_ID_TEST] = new XAudio2Sound(ixaudio2_);

		if(!SafeInitialize(xaudio2_sound_[i - BGM_ID_TEST]))
		{
			SafeRelease(xaudio2_sound_[i - BGM_ID_TEST]);
			return false;
		}

		xaudio2_sound_[i - BGM_ID_TEST]->LoadFromResource(MAKEINTRESOURCE(i));
	}

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void BGM::Uninitialize(void)
{
	for(u32 i = BGM_ID_TEST;i < BGM_ID_MAX;++i)
	{
		SafeRelease(xaudio2_sound_[i - BGM_ID_TEST]);
	}
}

//=============================================================================
// update
//=============================================================================
void BGM::Update(void)
{
	if(frame_count_ <= fade_frame_)
	{
		frame_count_++;

		if(preview_bgm_ != BGM_ID_NONE && current_bgm_ != preview_bgm_)
		{
			xaudio2_sound_[preview_bgm_ - BGM_ID_TEST]->SetVolume(volume_ / fade_frame_ * ((s32)fade_frame_ - (s32)frame_count_));

			if(xaudio2_sound_[preview_bgm_ - BGM_ID_TEST]->__volume() <= 0.0f)
			{
				xaudio2_sound_[preview_bgm_ - BGM_ID_TEST]->Stop();
			}
		}

		if(current_bgm_ != BGM_ID_NONE)
		{
			xaudio2_sound_[current_bgm_ - BGM_ID_TEST]->SetVolume(volume_ / fade_frame_ * frame_count_);
		}
	}
}

//=============================================================================
// play
//=============================================================================
bool BGM::Play(const BGM_ID& bgm_id)
{
	if(preview_bgm_ != BGM_ID_NONE)
	{
		if(xaudio2_sound_[preview_bgm_ - BGM_ID_TEST]->__is_play())
		{
			xaudio2_sound_[preview_bgm_ - BGM_ID_TEST]->Stop();
		}
	}

	preview_bgm_ = current_bgm_;
	current_bgm_ = bgm_id;

	if(current_bgm_ != BGM_ID_NONE)
	{
		if(is_fade_)
		{
			frame_count_ = 0;
			xaudio2_sound_[current_bgm_ - BGM_ID_TEST]->SetVolume(0.0f);
		}
		else
		{
			frame_count_ = fade_frame_;
			xaudio2_sound_[current_bgm_ - BGM_ID_TEST]->SetVolume(volume_);
		}

		if(is_loop_)
		{
			return xaudio2_sound_[current_bgm_ - BGM_ID_TEST]->Play(0);
		}
		else
		{
			return xaudio2_sound_[current_bgm_ - BGM_ID_TEST]->Play(1);
		}
	}

	return false;
}

//=============================================================================
// stop
//=============================================================================
void BGM::Stop(void)
{
	if(current_bgm_ != BGM_ID_NONE)
	{
		xaudio2_sound_[current_bgm_ - BGM_ID_TEST]->Stop();
	}

	if(preview_bgm_ != BGM_ID_NONE)
	{
		xaudio2_sound_[preview_bgm_ - BGM_ID_TEST]->Stop();
	}
}

//=============================================================================
// set volume
//=============================================================================
void BGM::SetVolume(const f32& volume)
{
	volume_ = volume;

	if(volume_ < 0.0f)
	{
		volume_ = 0.0f;
	}

	if(current_bgm_ != BGM_ID_NONE)
	{
		xaudio2_sound_[current_bgm_ - BGM_ID_TEST]->SetVolume(volume_);
	}
}

//---------------------------------- EOF --------------------------------------
