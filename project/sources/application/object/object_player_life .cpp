//*****************************************************************************
//
// object_player_life
//
// Author	: masato masuda
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "object_player_life .h"
#include "object_life.h"
#include "render/sprite.h"
#include "system/system.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const f32 scale = 0.9f;
const D3DXVECTOR2 ObjectPlayerLife::LIFE_SIZE = D3DXVECTOR2(46.0f * scale,38.0f * scale);
const D3DXVECTOR2 ObjectPlayerLife::LIFE_POSITION = D3DXVECTOR2(0.0f,0.0f);

//=============================================================================
// constructor
//=============================================================================
ObjectPlayerLife::ObjectPlayerLife(void)
	: life_(0)
	, provision_position_(0.0f, 0.0f)
{
	for(int i = 0 ; i < LIFE_MAX ; i++){
		life_icon_[i] = nullptr;
	}
}

//=============================================================================
// destructor
//=============================================================================
ObjectPlayerLife::~ObjectPlayerLife(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool ObjectPlayerLife::Initialize(void)
{
	for(int i = 0 ; i < LIFE_MAX ; i++)
	{
		life_icon_[i] = new ObjectLife();
		life_icon_[i]->Initialize();
		life_icon_[i]->__is_life(true);

		const D3DXVECTOR2 position = D3DXVECTOR2(LIFE_POSITION.x + (LIFE_SIZE.x * i), LIFE_POSITION.y);
		life_icon_[i]->__position(position);
		life_icon_[i]->__size(LIFE_SIZE);
	}

	provision_position_ = LIFE_POSITION;

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void ObjectPlayerLife::Uninitialize(void)
{
	for(int i = 0 ; i < LIFE_MAX ; i++){
		SafeRelease(life_icon_[i]);
	}
}

//=============================================================================
// update
//=============================================================================
void ObjectPlayerLife::Update(void)
{
	for(int i = 0 ; i < LIFE_MAX ; i++){

		if(i < life_)
		{
			life_icon_[i]->__is_life(true);
		}
		else
		{
			life_icon_[i]->__is_life(false);
		}
		life_icon_[i]->Update();
	}
}

//=============================================================================
// draw
//=============================================================================
void ObjectPlayerLife::Draw(void)
{
	for(int i = 0 ; i < LIFE_MAX ; i++){
		life_icon_[i]->Draw();
	}
}

//=============================================================================
// __position
//=============================================================================
void ObjectPlayerLife::__position(const D3DXVECTOR2 position)
{
	provision_position_ = position;

	for(int i = 0 ; i < LIFE_MAX ; i++)
	{
		const D3DXVECTOR2 pos = D3DXVECTOR2(provision_position_.x + (LIFE_SIZE.x * i), provision_position_.y);
		life_icon_[i]->__position(pos);
	}
}


//---------------------------------- EOF --------------------------------------
