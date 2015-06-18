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
const u32 ObjectPlayer::ANIMATION_DATA_SIZE[ANIMATION_TYPE_MAX] =
{
	ANIMATION_DATA_SIZE_WAIT,
	ANIMATION_DATA_SIZE_RUN,
	ANIMATION_DATA_SIZE_JUMP,
	ANIMATION_DATA_SIZE_FALL,
	ANIMATION_DATA_SIZE_LIGHT_START,
	ANIMATION_DATA_SIZE_LIGHT_END,
	ANIMATION_DATA_SIZE_LIGHT,
	ANIMATION_DATA_SIZE_DAMAGE,
	ANIMATION_DATA_SIZE_GAME_START,
	ANIMATION_DATA_SIZE_GAME_END,
};

const Animation::DATA ObjectPlayer::WAIT_ANIMATION_DATA[ANIMATION_DATA_SIZE_WAIT] =
{
	Animation::DATA(8,1,0),
	Animation::DATA(8,2,1),
	Animation::DATA(8,3,2),
	Animation::DATA(8,4,3),
	Animation::DATA(8,0,4),
};

const Animation::DATA ObjectPlayer::RUN_ANIMATION_DATA[ANIMATION_DATA_SIZE_RUN] =
{
	Animation::DATA(4,1,0),
	Animation::DATA(4,2,1),
	Animation::DATA(4,3,2),
	Animation::DATA(4,4,3),
	Animation::DATA(4,5,4),
	Animation::DATA(4,0,5),
};

const Animation::DATA ObjectPlayer::JUMP_ANIMATION_DATA[ANIMATION_DATA_SIZE_JUMP] =
{
	Animation::DATA(2,1,0),
	Animation::DATA(2,2,1),
	Animation::DATA(2,3,2),
	Animation::DATA(2,4,3),
	Animation::DATA(2,5,4),
	Animation::DATA(2,0,5),
};

const Animation::DATA ObjectPlayer::FALL_ANIMATION_DATA[ANIMATION_DATA_SIZE_FALL] =
{
	Animation::DATA(5,1,0),
	Animation::DATA(5,2,1),
	Animation::DATA(5,0,2),
};

const Animation::DATA ObjectPlayer::LIGHT_START_ANIMATION_DATA[ANIMATION_DATA_SIZE_LIGHT_START] = 
{
	Animation::DATA(4,0,0),
};

const Animation::DATA ObjectPlayer::LIGHT_END_ANIMATION_DATA[ANIMATION_DATA_SIZE_LIGHT_END] =
{
	Animation::DATA(4,0,0),
};

const Animation::DATA ObjectPlayer::LIGHT_ANIMATION_DATA[ANIMATION_DATA_SIZE_LIGHT] =
{
	Animation::DATA(4,1,0),
	Animation::DATA(4,2,1),
	Animation::DATA(4,3,2),
	Animation::DATA(4,4,3),
	Animation::DATA(4,5,4),
	Animation::DATA(4,0,5),
};

const Animation::DATA ObjectPlayer::DAMAGE_ANIMATION_DATA[ANIMATION_DATA_SIZE_DAMAGE] =
{
	Animation::DATA(4,0,0),
};

const Animation::DATA ObjectPlayer::GAME_START_ANIMATION_DATA[ANIMATION_DATA_SIZE_GAME_START] =
{
	Animation::DATA(4,0,0),
};

const Animation::DATA ObjectPlayer::GAME_END_ANIMATION_DATA[ANIMATION_DATA_SIZE_GAME_END] =
{
	Animation::DATA(4,0,0),
};

const Animation::DATA* ObjectPlayer::ANIMATION_DATA[ANIMATION_TYPE_MAX] =
{
	WAIT_ANIMATION_DATA,
	RUN_ANIMATION_DATA,
	JUMP_ANIMATION_DATA,
	FALL_ANIMATION_DATA,
	LIGHT_START_ANIMATION_DATA,
	LIGHT_END_ANIMATION_DATA,
	LIGHT_ANIMATION_DATA,
	DAMAGE_ANIMATION_DATA,
	GAME_START_ANIMATION_DATA,
	GAME_END_ANIMATION_DATA
};

const ObjectPlayer::ANIMATION_TEXTURE_DATA ObjectPlayer::TEXTURE_DATA[ANIMATION_TYPE_MAX] =
{
	ANIMATION_TEXTURE_DATA(Texture::TEXTURE_ID_NYAS_STAND,5,1),
	ANIMATION_TEXTURE_DATA(Texture::TEXTURE_ID_NYAS_RUN,3,2),
	ANIMATION_TEXTURE_DATA(Texture::TEXTURE_ID_NYAS_JUMP,3,2),
	ANIMATION_TEXTURE_DATA(Texture::TEXTURE_ID_NYAS_FALL,3,1),
	ANIMATION_TEXTURE_DATA(Texture::TEXTURE_ID_NYAS_LIGHT_BEGIN,1,1),
	ANIMATION_TEXTURE_DATA(Texture::TEXTURE_ID_NYAS_LIGHT_END,1,1),
	ANIMATION_TEXTURE_DATA(Texture::TEXTURE_ID_NYAS_LIGHT,6,1),
	ANIMATION_TEXTURE_DATA(Texture::TEXTURE_ID_NYAS_DAMAGE,1,1),
	ANIMATION_TEXTURE_DATA(Texture::TEXTURE_ID_NYAS_START,1,1),
	ANIMATION_TEXTURE_DATA(Texture::TEXTURE_ID_NYAS_CLEAR,1,1),
};

const D3DXVECTOR2 ObjectPlayer::DEFAULT_SIZE = D3DXVECTOR2(200.0f,200.0f);

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
	player_->Initialize();
	size_ = DEFAULT_SIZE;

	animation_ = new Animation();
	animation_type_ = ANIMATION_TYPE_MAX;
	StartAnimation(ANIMATION_TYPE_WAIT);
	animation_->Add(ANIMATION_DATA[animation_type_],sizeof(ANIMATION_DATA) * ANIMATION_DATA_SIZE[animation_type_]);
	player_->__size(size_);
	player_->__position(position_);
	player_->__point(Sprite::POINT_CENTER);
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
// start animation
//=============================================================================
void ObjectPlayer::StartAnimation(ANIMATION_TYPE animation_type)
{
	if(animation_type_ != animation_type)
	{
		animation_type_ = animation_type;
		animation_->Clear();
		animation_->Add(ANIMATION_DATA[animation_type_],sizeof(ANIMATION_DATA) * ANIMATION_DATA_SIZE[animation_type_]);
		animation_->Start(0);
		player_->__texture_id((Texture::TEXTURE_ID)TEXTURE_DATA[animation_type_]._texture_id);
		player_->__division_width((Texture::TEXTURE_ID)TEXTURE_DATA[animation_type_]._division_width);
		player_->__division_height((Texture::TEXTURE_ID)TEXTURE_DATA[animation_type_]._division_height);
		player_->SetParameter();
	}
}

//=============================================================================
// set size
//=============================================================================
void ObjectPlayer::SetSize(const D3DXVECTOR2& size)
{
	size_ = size;
	player_->__size(size_);
	player_->SetParameter();
}

//---------------------------------- EOF --------------------------------------
