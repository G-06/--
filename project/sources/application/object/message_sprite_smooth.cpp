//*****************************************************************************
//
// message_sprite_smooth
//
// Author	: masato masuda
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "message_sprite_smooth.h"
#include "render/sprite.h"
#include "system/system.h"
#include "system/directx9/texture/texture.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 MessageSpriteSmooth::DEFAULT_POSITION = D3DXVECTOR2(0.0f, 0.0f);
const D3DXVECTOR2 MessageSpriteSmooth::DEFAULT_SIZE = D3DXVECTOR2(0.0f, 0.0f);

const D3DXVECTOR2 CLEAR_VECTOR2 = D3DXVECTOR2(0.0f, 0.0f);
const D3DXCOLOR CLEAR_COLOR = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
const f32 HALF_PI = D3DX_PI / 2.0f;


//=============================================================================
// constructor
//=============================================================================
MessageSpriteSmooth::MessageSpriteSmooth(void)
	:sprite_(nullptr)
	,dest_frame_(0)
	,now_frame_(0)
	,move_flag_(false)
	,dest_position_(CLEAR_VECTOR2)
	,dest_size_(CLEAR_VECTOR2)
	,dest_color_(CLEAR_COLOR)
	,target_position_(CLEAR_VECTOR2)
	,target_size_(CLEAR_VECTOR2)
	,target_color_(CLEAR_COLOR)
	,old_position_(CLEAR_VECTOR2)
	,old_size_(CLEAR_VECTOR2)
	,old_color_(CLEAR_COLOR)
{
}

//=============================================================================
// destructor
//=============================================================================
MessageSpriteSmooth::~MessageSpriteSmooth(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool MessageSpriteSmooth::Initialize(void)
{
	sprite_ = new Sprite();
	sprite_->Initialize();
	sprite_->__size(DEFAULT_SIZE);
	sprite_->__position(DEFAULT_POSITION);
	sprite_->__point(Sprite::POINT_CENTER);
	sprite_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_000);
	sprite_->SetParameter();
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void MessageSpriteSmooth::Uninitialize(void)
{
	SafeRelease(sprite_);
}

//=============================================================================
// update
//=============================================================================
void MessageSpriteSmooth::Update(void)
{
	if(move_flag_)
	{
		if(dest_frame_ > now_frame_)
		{
			const float s = ( 1 + sinf( -HALF_PI + ( D3DX_PI / dest_frame_ * now_frame_ ) ) ) / 2.0f;

			const D3DXVECTOR2 position = old_position_ + target_position_ * s;
			const D3DXVECTOR2 size = old_size_ + target_size_ * s;
			const D3DXCOLOR color = (D3DXCOLOR)old_color_ + (D3DXCOLOR)target_color_ * s;

			sprite_->__position(position);
			sprite_->__size(size);
			sprite_->__color(color);
			sprite_->SetParameter();

			now_frame_ ++;
		}
		else
		{
			move_flag_ = false;
			now_frame_ = 0;

			sprite_->__position(dest_position_);
			sprite_->__size(dest_size_);
			sprite_->__color(dest_color_);
			sprite_->SetParameter();
		}
	}
}

//=============================================================================
// draw
//=============================================================================
void MessageSpriteSmooth::Draw(void)
{
	sprite_->Draw();
}

//=============================================================================
// StartMove
//-----------------------------------------------------------------------------
// dest‚ð‘S‚ÄÝ’è‚µ‚Ä‚©‚çŒÄ‚ñ‚Å‚Ë
//=============================================================================
void MessageSpriteSmooth::StartMove(void)
{
	move_flag_			= true;
	dest_frame_			-= now_frame_;
	now_frame_			= 0;
	target_position_	= dest_position_ - sprite_->__position();
	target_size_		= dest_size_ - sprite_->__size();
	target_color_		= dest_color_ - (D3DXCOLOR)sprite_->__color();
	old_position_		= sprite_->__position();
	old_size_			= sprite_->__size();
	old_color_			= sprite_->__color();
}

//=============================================================================
// SyncConf
//-----------------------------------------------------------------------------
// ¡‚ÌÝ’è‚Æ“¯Šú‚³‚¹‚é
//=============================================================================
void MessageSpriteSmooth::SynchroParameter(void)
{
	dest_position_ = sprite_->__position();
	dest_size_ = sprite_->__size();
	dest_color_ = sprite_->__color();
}

//=============================================================================
// ForcingDest
//-----------------------------------------------------------------------------
// ‘S‚Ä‚ðDest‚É‡‚í‚¹‚ÄI—¹
//=============================================================================
void MessageSpriteSmooth::ForcingDest(void)
{
	sprite_->__position(dest_position_);
	sprite_->__size(dest_size_);
	sprite_->__color(dest_color_);
	sprite_->SetParameter();

	dest_frame_ = 0;
	now_frame_ = 0;
	move_flag_ = false;
}

//=============================================================================
// __position
//=============================================================================
void MessageSpriteSmooth::__position(const D3DXVECTOR2& position)
{
	sprite_->__position(position);
	sprite_->SetParameter();
}

//=============================================================================
// __position
//=============================================================================
const D3DXVECTOR2& MessageSpriteSmooth::__position(void)const
{
	return sprite_->__position();
}

//=============================================================================
// __size
//=============================================================================
void MessageSpriteSmooth::__size(const D3DXVECTOR2& size)
{
	sprite_->__size(size);
	sprite_->SetParameter();
}

//=============================================================================
// __size
//=============================================================================
const D3DXVECTOR2& MessageSpriteSmooth::__size(void)const
{
	return sprite_->__size();
}

//=============================================================================
// __color
//=============================================================================
void MessageSpriteSmooth::__color(const D3DXCOLOR& color)
{
	sprite_->__color(color);
	sprite_->SetParameter();
}

//=============================================================================
// __texture_id
//=============================================================================
void MessageSpriteSmooth::__texture_id(const Texture::TEXTURE_ID& texture_id)
{
	sprite_->__texture_id(texture_id);
	sprite_->SetParameter();
}


//---------------------------------- EOF --------------------------------------
