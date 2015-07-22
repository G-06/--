//*****************************************************************************
//
// title logo
//
// Author	: masato masuda
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "title_logo.h"
#include "render/sprite.h"
#include "system/system.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const f32 scale = 0.8f;
const D3DXVECTOR2 TitleLogo::DEFAULT_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f,300.0f);
const D3DXVECTOR2 TitleLogo::DEFAULT_SIZE = D3DXVECTOR2(1024.0f * scale, 604.0f * scale);
const u32 DEST_FRAME = 30;
const f32 HALF_PI = D3DX_PI / 2.0f;

//=============================================================================
// constructor
//=============================================================================
TitleLogo::TitleLogo(void)
	:sprite_(nullptr)
	,dest_position_(0.0f,0.0f)
	,target_position_(0.0f,0.0f)
	,old_position_(0.0f,0.0f)
	,dest_frame_(DEST_FRAME)
	,now_frame_(0)
	,is_move_(0)
{
}

//=============================================================================
// destructor
//=============================================================================
TitleLogo::~TitleLogo(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool TitleLogo::Initialize(void)
{
	sprite_ = new Sprite();
	sprite_->Initialize();
	sprite_->__size(DEFAULT_SIZE);
	sprite_->__position(DEFAULT_POSITION);
	sprite_->__point(Sprite::POINT_CENTER);
	sprite_->__texture_id(Texture::TEXTURE_ID_TITLE_LOGO);
	sprite_->SetParameter();

	dest_position_ = DEFAULT_POSITION;
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void TitleLogo::Uninitialize(void)
{
	SafeRelease(sprite_);
}

//=============================================================================
// update
//=============================================================================
void TitleLogo::Update(void)
{
	if(is_move_)
	{
		if(dest_frame_ > now_frame_)
		{
			const float s = ( 1 + sinf( -HALF_PI + ( D3DX_PI / dest_frame_ * now_frame_ ) ) ) / 2.0f;
			const D3DXVECTOR2 position = old_position_ + target_position_ * s;

			sprite_->__position(position);
			sprite_->SetParameter();

			now_frame_ ++;
		}
		else
		{
			is_move_ = false;
			now_frame_ = 0;

			sprite_->__position(dest_position_);
			sprite_->SetParameter();
		}
	}
}

//=============================================================================
// draw
//=============================================================================
void TitleLogo::Draw(void)
{
	sprite_->Draw();
}

//=============================================================================
// StartMove
//-----------------------------------------------------------------------------
// dest‚ð‘S‚ÄÝ’è‚µ‚Ä‚©‚çŒÄ‚ñ‚Å‚Ë
//=============================================================================
void TitleLogo::StartMove(void)
{
	is_move_			= true;
	dest_frame_			-= now_frame_;
	now_frame_			= 0;
	target_position_	= dest_position_ - sprite_->__position();
	old_position_		= sprite_->__position();
}

//---------------------------------- EOF --------------------------------------
