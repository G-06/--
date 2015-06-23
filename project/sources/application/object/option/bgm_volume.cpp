//*****************************************************************************
//
// bgm volume
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "bgm_volume.h"
#include "render/sprite.h"
#include "system/system.h"
#include "../option.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const f32 BgmVolume::VOLUME_MAX = 1.0f;
const f32 BgmVolume::VOLUME_MIN = 0.0f;
const D3DXVECTOR2 BgmVolume::SIZE = D3DXVECTOR2(270.0f,30.0f);

//=============================================================================
// constructor
//=============================================================================
BgmVolume::BgmVolume(void)
	:bgm_volume_(1.0f)
{
}

//=============================================================================
// destructor
//=============================================================================
BgmVolume::~BgmVolume(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool BgmVolume::Initialize(void)
{
	volume_gage_ = new Sprite();
	volume_gage_->Initialize();
	volume_gage_->__size(D3DXVECTOR2(bgm_volume_ * SIZE.x,SIZE.y));
	volume_gage_->__position(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width()/2,225.f));
	volume_gage_->SetParameter();

	bgm_button_ = new Sprite();
	bgm_button_->Initialize();
	bgm_button_->__size(Option::DEFAULT_MENU_SIZE);
	bgm_button_->__position(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width()/2 - 250,225.f));
	bgm_button_->__texture_id(Texture::TEXTURE_ID_OPTION_STRING_BGM_VOLUME);
	bgm_button_->__point(Sprite::POINT_CENTER);
	bgm_button_->SetParameter();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void BgmVolume::Uninitialize(void)
{
	SafeRelease(volume_gage_);
	SafeRelease(bgm_button_);
}

//=============================================================================
// update
//=============================================================================
void BgmVolume::Update(void)
{
}

//=============================================================================
// draw
//=============================================================================
void BgmVolume::Draw(void)
{
	bgm_button_->Draw();
	volume_gage_->Draw();
}

//=============================================================================
// Adjustvolume
//=============================================================================
void BgmVolume::Adjustvolume(f32 volume)
{
	if(volume > VOLUME_MAX)
	{
		volume = VOLUME_MAX;
	}

	if(volume < VOLUME_MIN)
	{
		volume = VOLUME_MIN;
	}

	bgm_volume_ = volume;
	volume_gage_->__size(D3DXVECTOR2(bgm_volume_ * SIZE.x,SIZE.y));
	volume_gage_->SetParameter();
}

//=============================================================================
// select
//=============================================================================
void BgmVolume::Select(bool is_select)
{
	if(is_select == true)
	{
		bgm_button_->__size(Option::EXPAND_MENU_SIZE);
	}
	else
	{
		bgm_button_->__size(Option::DEFAULT_MENU_SIZE);
	}
	
	bgm_button_->SetParameter();
}


//---------------------------------- EOF --------------------------------------
