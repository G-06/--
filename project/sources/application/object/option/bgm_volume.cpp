//*****************************************************************************
//
// bgm volume
//
// Author		: Ryotaro Arai
//				: masato masuda
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "bgm_volume.h"
#include "render/sprite.h"
#include "system/system.h"
#include "../option.h"
#include "object/option/option_sprite_smooth.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
// string
const D3DXVECTOR2 DEFAULT_SIZE = Option::DEFAULT_MENU_SIZE;
const D3DXVECTOR2 DEFAULT_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f - 250, 205.f);
// gauge
const D3DXVECTOR2 DEFAULT_NUM_SIZE = D3DXVECTOR2(DEFAULT_SIZE.y, DEFAULT_SIZE.y);
const D3DXVECTOR2 DEFAULT_NUM_POSITION = D3DXVECTOR2(DEFAULT_POSITION.x + 300.0f, DEFAULT_POSITION.y);

const f32 BgmVolume::VOLUME_MAX = 1.0f;
const f32 BgmVolume::VOLUME_MIN = 0.0f;
const D3DXVECTOR2 SIZE_SCALE = D3DXVECTOR2(0.6f, 0.8f);
const D3DXVECTOR2 BgmVolume::SIZE = D3DXVECTOR2(470.0f * SIZE_SCALE.x,78.0f * SIZE_SCALE.y);

//=============================================================================
// constructor
//=============================================================================
BgmVolume::BgmVolume(void)
	:bgm_volume_(1.0f)
	,volume_gauge_(NULL)
	,volume_gauge_frame_(NULL)
	,volume_gauge_back_(NULL)
	,bgm_string_(NULL)
	,bgm_string_frame_(NULL)
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
	// gauge
	volume_gauge_ = new OptionSpriteSmooth();
	volume_gauge_->Initialize();
	volume_gauge_->__size(D3DXVECTOR2(bgm_volume_ * SIZE.x,SIZE.y));
	volume_gauge_->__position(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width()/2,225.f));
	volume_gauge_->__point(Sprite::POINT_LEFT_UP);
	volume_gauge_->__texture_id(Texture::TEXTURE_ID_OPTION_BGM_BAR);

	volume_gauge_frame_ = new OptionSpriteSmooth();
	volume_gauge_frame_->Initialize();
	volume_gauge_frame_->__size(D3DXVECTOR2(SIZE.x,SIZE.y));
	volume_gauge_frame_->__position(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width()/2,225.f));
	volume_gauge_frame_->__point(Sprite::POINT_LEFT_UP);
	volume_gauge_frame_->__texture_id(Texture::TEXTURE_ID_OPTION_BGM_BAR_FRAME);

	volume_gauge_back_ = new OptionSpriteSmooth();
	volume_gauge_back_->Initialize();
	volume_gauge_back_->__size(D3DXVECTOR2(SIZE.x,SIZE.y));
	volume_gauge_back_->__position(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width()/2,225.f));
	volume_gauge_back_->__point(Sprite::POINT_LEFT_UP);
	volume_gauge_back_->__texture_id(Texture::TEXTURE_ID_OPTION_BGM_BAR_BACK);

	// string
	bgm_string_ = new OptionSpriteSmooth();
	bgm_string_->Initialize();
	bgm_string_->__size(DEFAULT_SIZE);
	bgm_string_->__position(DEFAULT_POSITION);
	bgm_string_->__texture_id(Texture::TEXTURE_ID_OPTION_STRING_BGM_VOLUME);

	bgm_string_frame_ = new OptionSpriteSmooth();
	bgm_string_frame_->Initialize();
	bgm_string_frame_->__size(Option::DEFAULT_MENU_FRAME_SIZE);
	bgm_string_frame_->__position(DEFAULT_POSITION);
	bgm_string_frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_000);

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void BgmVolume::Uninitialize(void)
{
	SafeRelease(volume_gauge_);
	SafeRelease(volume_gauge_frame_);
	SafeRelease(volume_gauge_back_);
	SafeRelease(bgm_string_);
	SafeRelease(bgm_string_frame_);
}

//=============================================================================
// update
//=============================================================================
void BgmVolume::Update(void)
{
	bgm_string_->Update();
	bgm_string_frame_->Update();
	volume_gauge_->Update();
	volume_gauge_frame_->Update();
	volume_gauge_back_->Update();
}

//=============================================================================
// draw
//=============================================================================
void BgmVolume::Draw(void)
{
	bgm_string_frame_->Draw();
	bgm_string_->Draw();

	volume_gauge_back_->Draw();
	volume_gauge_->Draw();
	volume_gauge_frame_->Draw();
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
	volume_gauge_->__size(D3DXVECTOR2(bgm_volume_ * SIZE.x, SIZE.y));
	volume_gauge_->__right(bgm_volume_);
}

//=============================================================================
// select
//=============================================================================
void BgmVolume::Select(bool is_select)
{
	if(is_select == true)
	{
		bgm_string_frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_001);
	}
	else
	{
		bgm_string_frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_000);
	}
}

//=============================================================================
// __position
//=============================================================================
void BgmVolume::__position(const D3DXVECTOR2 position, const float offset_x)
{
	bgm_string_->__position(position);
	bgm_string_frame_->__position(position);

	volume_gauge_->__position(D3DXVECTOR2(position.x + offset_x, position.y - SIZE.y * 0.5f));
	volume_gauge_frame_->__position(D3DXVECTOR2(position.x + offset_x, position.y - SIZE.y * 0.5f));
	volume_gauge_back_->__position(D3DXVECTOR2(position.x + offset_x, position.y - SIZE.y * 0.5f));
}


//---------------------------------- EOF --------------------------------------
