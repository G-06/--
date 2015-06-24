//*****************************************************************************
//
// object player icon
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "object_player_icon.h"
#include "render/sprite.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 ObjectPlayerIcon::DEFAULT_SIZE = D3DXVECTOR2(256.0f*0.55f,256.0f*0.55f);
const u32 ObjectPlayerIcon::DIVISION_WIDTH = 1;
const u32 ObjectPlayerIcon::DIVISION_HEIGHT = 1;
const Animation::DATA ObjectPlayerIcon::ANIMATION_DATA[] =
{
	Animation::DATA(8,0,0),
};

//=============================================================================
// constructor
//=============================================================================
ObjectPlayerIcon::ObjectPlayerIcon(void)
{
}

//=============================================================================
// destructor
//=============================================================================
ObjectPlayerIcon::~ObjectPlayerIcon(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool ObjectPlayerIcon::Initialize(void)
{
	sprite_ = new Sprite();
	sprite_->Initialize();
	sprite_->__point(Sprite::POINT_LEFT_MIDDLE);
	sprite_->__size(DEFAULT_SIZE);
	sprite_->__texture_id(Texture::TEXTURE_ID_GAME_NYAS_ICON);
	sprite_->__division_width(DIVISION_WIDTH);
	sprite_->__division_height(DIVISION_HEIGHT);
	sprite_->SetParameter();

	animation_ = new Animation();
	animation_->Initialize();
	animation_->Add(ANIMATION_DATA,sizeof(ANIMATION_DATA) / sizeof(Animation::DATA));
	animation_->Start(0);

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void ObjectPlayerIcon::Uninitialize(void)
{
	SafeRelease(sprite_);

	SafeRelease(animation_);
}

//=============================================================================
// update
//=============================================================================
void ObjectPlayerIcon::Update(void)
{
	animation_->Update();

	sprite_->__index(animation_->__current_index());
	sprite_->SetParameter();
}

//=============================================================================
// draw
//=============================================================================
void ObjectPlayerIcon::Draw(void)
{
	sprite_->__position(position_);
	sprite_->Draw();
}

//---------------------------------- EOF --------------------------------------
