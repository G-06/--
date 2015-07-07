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
#include "object/option/option_sprite_smooth.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
// string
const D3DXVECTOR2 DEFAULT_SIZE = Option::DEFAULT_MENU_SIZE;
const D3DXVECTOR2 DEFAULT_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f - 250, 275.0f);
// gauge
const D3DXVECTOR2 DEFAULT_NUM_SIZE = D3DXVECTOR2(DEFAULT_SIZE.y, DEFAULT_SIZE.y);
const D3DXVECTOR2 DEFAULT_NUM_POSITION = D3DXVECTOR2(DEFAULT_POSITION.x + 300.0f, DEFAULT_POSITION.y);


//=============================================================================
// constructor
//=============================================================================
SeVolume::SeVolume(void)
	:se_volume_(5.0f)
	,volume_gauge_(NULL)
	,se_string_(NULL)
	,se_string_frame_(NULL)
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
	volume_gauge_ = new OptionSpriteSmooth();
	volume_gauge_->Initialize();
	volume_gauge_->__size(D3DXVECTOR2(se_volume_* (DEFAULT_SIZE.x), DEFAULT_SIZE.y));
	volume_gauge_->__position(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width()/2,275.f));
	volume_gauge_->__point(Sprite::POINT_LEFT_UP);

	se_string_ = new OptionSpriteSmooth();
	se_string_->Initialize();
	se_string_->__size(DEFAULT_SIZE);
	se_string_->__position(DEFAULT_POSITION);
	se_string_->__texture_id(Texture::TEXTURE_ID_OPTION_STRING_SE_VOLUME);

	se_string_frame_ = new OptionSpriteSmooth();
	se_string_frame_->Initialize();
	se_string_frame_->__size(DEFAULT_SIZE);
	se_string_frame_->__position(DEFAULT_POSITION);
	se_string_frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_000);

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void SeVolume::Uninitialize(void)
{
	SafeRelease(volume_gauge_);
	SafeRelease(se_string_);
	SafeRelease(se_string_frame_);
}

//=============================================================================
// update
//=============================================================================
void SeVolume::Update(void)
{
	se_string_->Update();
	se_string_frame_->Update();
	volume_gauge_->Update();
}

//=============================================================================
// draw
//=============================================================================
void SeVolume::Draw(void)
{
	se_string_frame_->Draw();
	se_string_->Draw();
	volume_gauge_->Draw();
}

//=============================================================================
// Adjustvolume
//=============================================================================
void SeVolume::Adjustvolume(f32 volume)
{
	se_volume_ = volume;
	volume_gauge_->__size(D3DXVECTOR2(se_volume_ * (DEFAULT_SIZE.x * 1.5f), DEFAULT_SIZE.y));
}

//=============================================================================
// select
//=============================================================================
void SeVolume::Select(bool is_select)
{
	if(is_select == true)
	{
		se_string_frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_001);
	}
	else
	{
		se_string_frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_000);
	}
}

//=============================================================================
// __position
//=============================================================================
void SeVolume::__position(const D3DXVECTOR2 position, const float offset_x)
{
	se_string_->__position(position);
	se_string_frame_->__position(position);
	volume_gauge_->__position(D3DXVECTOR2(position.x + offset_x, position.y - DEFAULT_SIZE.y * 0.5f));
}


//---------------------------------- EOF --------------------------------------
