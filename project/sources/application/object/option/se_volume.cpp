//*****************************************************************************
//
// se volume
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "se_volume.h"
#include "render/sprite.h"
#include "system/system.h"
#include "../option.h"

//=============================================================================
// constructor
//=============================================================================
SeVolume::SeVolume(void)
{
}

//=============================================================================
// destructor
//=============================================================================
SeVolume::~SeVolume(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool SeVolume::Initialize(void)
{
	se_volume_ = 5;

	volume_gage_ = new Sprite();
	volume_gage_->Initialize();
	volume_gage_->__size(D3DXVECTOR2(se_volume_*30.f, 30.f));
	volume_gage_->__position(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width()/2,275.f));
	volume_gage_->SetParameter();

	se_button_ = new Sprite();
	se_button_->Initialize();
	se_button_->__size(Option::DEFAULT_MENU_SIZE);
	se_button_->__position(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width()/2 - 250,275.0f));
	se_button_->__texture_id(Texture::TEXTURE_ID_OPTION_STRING_SE_VOLUME);
	se_button_->__point(Sprite::POINT_CENTER);
	se_button_->SetParameter();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void SeVolume::Uninitialize(void)
{
	SafeRelease(volume_gage_);
	SafeRelease(se_button_);
}

//=============================================================================
// update
//=============================================================================
void SeVolume::Update(void)
{
}

//=============================================================================
// draw
//=============================================================================
void SeVolume::Draw(void)
{
	se_button_->Draw();
	volume_gage_->Draw();
}

//=============================================================================
// Adjustvolume
//=============================================================================
void SeVolume::Adjustvolume(u32 volume)
{
	if(se_volume_ + volume <= 9 && se_volume_ + volume >= 0)
	{
		se_volume_ += volume;
		volume_gage_->__size(D3DXVECTOR2(se_volume_*30.f, 30.0f));
		volume_gage_->SetParameter();
	}
}

//=============================================================================
// select
//=============================================================================
void SeVolume::Select(bool is_select)
{
	if(is_select == true)
	{
		se_button_->__size(Option::EXPAND_MENU_SIZE);
	}
	else
	{
		se_button_->__size(Option::DEFAULT_MENU_SIZE);
	}
	
	se_button_->SetParameter();
}


//---------------------------------- EOF --------------------------------------
