//*****************************************************************************
//
// option_sprite_smooth
//
// Author	: masato masuda
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "option_sprite_smooth.h"
#include "render/sprite.h"
#include "system/system.h"
#include "system/directx9/texture/texture.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 OptionSpriteSmooth::DEFAULT_POSITION = D3DXVECTOR2(0.0f, 0.0f);
const D3DXVECTOR2 OptionSpriteSmooth::DEFAULT_SIZE = D3DXVECTOR2(0.0f, 0.0f);

const D3DXVECTOR2 CLEAR_VECTOR2 = D3DXVECTOR2(0.0f, 0.0f);
const D3DXCOLOR CLEAR_COLOR = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
const f32 HALF_PI = D3DX_PI / 2.0f;


//=============================================================================
// constructor
//=============================================================================
OptionSpriteSmooth::OptionSpriteSmooth(void)
	:sprite_(nullptr)
	,dest_frame_(0)
	,now_frame_(0)
	,is_move_(false)
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
OptionSpriteSmooth::~OptionSpriteSmooth(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool OptionSpriteSmooth::Initialize(void)
{
	sprite_ = new Sprite();
	sprite_->Initialize();
	sprite_->__size(DEFAULT_SIZE);
	sprite_->__position(DEFAULT_POSITION);
	sprite_->__point(Sprite::POINT_CENTER);
	sprite_->SetParameter();
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void OptionSpriteSmooth::Uninitialize(void)
{
	SafeRelease(sprite_);
}

//=============================================================================
// update
//=============================================================================
void OptionSpriteSmooth::Update(void)
{
	if(is_move_)
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
			is_move_ = false;
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
void OptionSpriteSmooth::Draw(void)
{
	sprite_->Draw();
}

//=============================================================================
// StartMove
//-----------------------------------------------------------------------------
// dest‚ð‘S‚ÄÝ’è‚µ‚Ä‚©‚çŒÄ‚ñ‚Å‚Ë
//=============================================================================
void OptionSpriteSmooth::StartMove(void)
{
	is_move_			= true;
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
void OptionSpriteSmooth::SynchroParameter(void)
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
void OptionSpriteSmooth::ForcingDest(void)
{
	sprite_->__position(dest_position_);
	sprite_->__size(dest_size_);
	sprite_->__color(dest_color_);
	sprite_->SetParameter();

	dest_frame_ = 0;
	now_frame_ = 0;
	is_move_ = false;
}

//=============================================================================
// __position
//=============================================================================
void OptionSpriteSmooth::__position(const D3DXVECTOR2& position)
{
	sprite_->__position(position);
	sprite_->SetParameter();
}

//=============================================================================
// __position
//=============================================================================
const D3DXVECTOR2& OptionSpriteSmooth::__position(void)const
{
	return sprite_->__position();
}

//=============================================================================
// __size
//=============================================================================
void OptionSpriteSmooth::__size(const D3DXVECTOR2& size)
{
	sprite_->__size(size);
	sprite_->SetParameter();
}

//=============================================================================
// __size
//=============================================================================
const D3DXVECTOR2& OptionSpriteSmooth::__size(void)const
{
	return sprite_->__size();
}

//=============================================================================
// __color
//=============================================================================
void OptionSpriteSmooth::__color(const D3DXCOLOR& color)
{
	sprite_->__color(color);
	sprite_->SetParameter();
}

//=============================================================================
// __texture_id
//=============================================================================
void OptionSpriteSmooth::__texture_id(const Texture::TEXTURE_ID& texture_id)
{
	sprite_->__texture_id(texture_id);
	sprite_->SetParameter();
}

//=============================================================================
// __point
//=============================================================================
void OptionSpriteSmooth::__point(const Sprite::POINT point)
{
	sprite_->__point(point);
	sprite_->SetParameter();
}

//=============================================================================
// __right
//=============================================================================
void OptionSpriteSmooth::__right(const f32& right)
{
	sprite_->__right(right);
	sprite_->SetParameter();
}

//---------------------------------- EOF --------------------------------------
