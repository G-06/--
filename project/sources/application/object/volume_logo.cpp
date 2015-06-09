//*****************************************************************************
//
// volume logo
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "volume_logo.h"
#include "render/sprite.h"
#include "system/system.h"

//=============================================================================
// constructor
//=============================================================================
VolumeLogo::VolumeLogo(void)
{
}

//=============================================================================
// destructor
//=============================================================================
VolumeLogo::~VolumeLogo(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool VolumeLogo::Initialize(void)
{
	sprite_ = new Sprite();
	sprite_->Initialize();
	sprite_->__size(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width()/3*2,(f32)GET_SYSTEM.__window()->__height()/5*4));
	sprite_->__position(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width()/6+100.0f,(f32)GET_SYSTEM.__window()->__height()/10+100.0f));
	sprite_->__texture_id(Texture::TEXTURE_ID_VOLUME_BUTTON);
	sprite_->SetParameter();
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void VolumeLogo::Uninitialize(void)
{
	SafeRelease(sprite_);
}

//=============================================================================
// update
//=============================================================================
void VolumeLogo::Update(void)
{
}

//=============================================================================
// draw
//=============================================================================
void VolumeLogo::Draw(void)
{
	sprite_->Draw();
}

//---------------------------------- EOF --------------------------------------
