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

//=============================================================================
// constructor
//=============================================================================
BgmVolume::BgmVolume(void)
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
	bgm_volume_ = 5;

	volume_gage_ = new Sprite();
	volume_gage_->Initialize();
	volume_gage_->__size(D3DXVECTOR2(bgm_volume_*30.f, 30.f));
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
void BgmVolume::Adjustvolume(u32 volume)
{
	if(bgm_volume_ + volume <= 9 && bgm_volume_ + volume >= 0)
	{
		bgm_volume_ += volume;
		volume_gage_->__size(D3DXVECTOR2(bgm_volume_*30.f, 30.0f));
		volume_gage_->SetParameter();
	}
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
