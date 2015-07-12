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

const D3DXVECTOR2 SIZE_SCALE = D3DXVECTOR2(0.8f, 0.8f);
const D3DXVECTOR2 BAR_SIZE = D3DXVECTOR2(500.0f * SIZE_SCALE.x,100.0f * SIZE_SCALE.y);

//=============================================================================
// constructor
//=============================================================================
SeVolume::SeVolume(void)
	:se_volume_(5.0f)
	,volume_gauge_(NULL)
	,volume_gauge_frame_(NULL)
	,volume_gauge_back_(NULL)
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
	// gauge
	volume_gauge_ = new OptionSpriteSmooth();
	volume_gauge_->Initialize();
	volume_gauge_->__size(D3DXVECTOR2(se_volume_* BAR_SIZE.x, BAR_SIZE.y));
	volume_gauge_->__position(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width()/2,275.f));
	volume_gauge_->__point(Sprite::POINT_LEFT_UP);
	volume_gauge_->__texture_id(Texture::TEXTURE_ID_OPTION_SE_BAR);

	volume_gauge_frame_ = new OptionSpriteSmooth();
	volume_gauge_frame_->Initialize();
	volume_gauge_frame_->__size(BAR_SIZE);
	volume_gauge_frame_->__position(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width()/2,225.f));
	volume_gauge_frame_->__point(Sprite::POINT_LEFT_UP);
	volume_gauge_frame_->__texture_id(Texture::TEXTURE_ID_OPTION_BGM_BAR_FRAME);

	volume_gauge_back_ = new OptionSpriteSmooth();
	volume_gauge_back_->Initialize();
	volume_gauge_back_->__size(BAR_SIZE);
	volume_gauge_back_->__position(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width()/2,225.f));
	volume_gauge_back_->__point(Sprite::POINT_LEFT_UP);
	volume_gauge_back_->__texture_id(Texture::TEXTURE_ID_OPTION_BGM_BAR_BACK);

	// string
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
	SafeRelease(volume_gauge_frame_);
	SafeRelease(volume_gauge_back_);
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
	volume_gauge_frame_->Update();
	volume_gauge_back_->Update();
}

//=============================================================================
// draw
//=============================================================================
void SeVolume::Draw(void)
{
	se_string_frame_->Draw();
	se_string_->Draw();

	volume_gauge_back_->Draw();
	volume_gauge_->Draw();
	volume_gauge_frame_->Draw();
}

//=============================================================================
// Adjustvolume
//=============================================================================
void SeVolume::Adjustvolume(f32 volume)
{
	se_volume_ = volume;
	volume_gauge_->__size(D3DXVECTOR2(se_volume_ * BAR_SIZE.x, BAR_SIZE.y));
	volume_gauge_->__right(se_volume_);
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

	volume_gauge_->__position(D3DXVECTOR2(position.x + offset_x, position.y - BAR_SIZE.y * 0.5f));
	volume_gauge_frame_->__position(D3DXVECTOR2(position.x + offset_x, position.y - BAR_SIZE.y * 0.5f));
	volume_gauge_back_->__position(D3DXVECTOR2(position.x + offset_x, position.y - BAR_SIZE.y * 0.5f));
}


//---------------------------------- EOF --------------------------------------
