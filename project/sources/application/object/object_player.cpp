//*****************************************************************************
//
// object player
//
// Author		: Ryotaro Arai
//				: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "object_player.h"
#include "render/sprite.h"
#include "system/system.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const u32 ObjectPlayer::ANIMATION_RUN_START = (0);
const u32 ObjectPlayer::ANIMATION_WAIT_START = (6);
const u32 ObjectPlayer::ANIMATION_LIGHT_START = (7);
const Animation::DATA ObjectPlayer::ANIMATION_DATA[] =
{
	Animation::DATA(4, 1, 0),
	Animation::DATA(4, 2, 1),
	Animation::DATA(4, 3, 2),
	Animation::DATA(4, 4, 3),
	Animation::DATA(4, 5, 4),
	Animation::DATA(4, 0, 5),
	Animation::DATA(2, 6, 0),
	Animation::DATA(2, 7, 0),
};
const ObjectPlayer::ANIMATION_TEXTURE_DATA ObjectPlayer::TEXTURE_DATA[ANIMATION_TYPE_MAX] =
{
	ANIMATION_TEXTURE_DATA(Texture::TEXTURE_ID_PLAYER,3,2),
	ANIMATION_TEXTURE_DATA(Texture::TEXTURE_ID_PLAYER,3,2),
	ANIMATION_TEXTURE_DATA(Texture::TEXTURE_ID_LIGHT,1,1),
};

//=============================================================================
// constructor
//=============================================================================
ObjectPlayer::ObjectPlayer(void)
	:player_(nullptr)
	,animation_(nullptr)
{
}

//=============================================================================
// destructor
//=============================================================================
ObjectPlayer::~ObjectPlayer(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool ObjectPlayer::Initialize(void)
{
	is_flip_ = false;
	player_ = new Sprite();
	animation_ = new Animation();
	animation_->Add(ANIMATION_DATA, sizeof(ANIMATION_DATA));
	animation_type_ = ANIMATION_TYPE_WAIT;
	player_->Initialize();
	player_->__size(D3DXVECTOR2(200,200));
	player_->__position(position_);
	player_->__texture_id(Texture::TEXTURE_ID_PLAYER);
	player_->__division_height(2);
	player_->__division_width(3);
	player_->__index(ANIMATION_RUN_START);
	player_->SetParameter();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void ObjectPlayer::Uninitialize(void)
{
	SafeRelease(player_);
	SafeRelease(animation_);
}

//=============================================================================
// update
//=============================================================================
void ObjectPlayer::Update(void)
{
	animation_->Update();
	player_->__texture_id((Texture::TEXTURE_ID)TEXTURE_DATA[animation_type_]._texture_id);
	player_->__division_width((Texture::TEXTURE_ID)TEXTURE_DATA[animation_type_]._division_width);
	player_->__division_height((Texture::TEXTURE_ID)TEXTURE_DATA[animation_type_]._division_height);
	player_->__index(animation_->__current_index());
	player_->__is_flip(is_flip_);
	player_->SetParameter();
}

//=============================================================================
// draw
//=============================================================================
void ObjectPlayer::Draw(void)
{
	player_->__position(position_);
	player_->Draw();
}

//=============================================================================
// move
//=============================================================================
void ObjectPlayer::Run(void)
{
	if(animation_type_ != ANIMATION_TYPE_RUN)
	{
		animation_type_ = ANIMATION_TYPE_RUN;
		animation_->Start(ANIMATION_RUN_START);
	}
}

//=============================================================================
// jump
//=============================================================================
void ObjectPlayer::Jump(void)
{
}

//=============================================================================
// wait
//=============================================================================
void ObjectPlayer::Wait(void)
{
	if(animation_type_ != ANIMATION_TYPE_WAIT)
	{
		animation_type_ = ANIMATION_TYPE_WAIT;
		animation_->Start(ANIMATION_WAIT_START);
	}
}

//=============================================================================
// light
//=============================================================================
void ObjectPlayer::Light(void)
{
	if(animation_type_ != ANIMATION_TYPE_LIGHT)
	{
		animation_type_ = ANIMATION_TYPE_LIGHT;
		animation_->Start(ANIMATION_LIGHT_START);
	}
}

//---------------------------------- EOF --------------------------------------
