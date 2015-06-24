//*****************************************************************************
//
// game bg
//
// Author		: taichi kitazawa
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "game_bg.h"
#include "system/system.h"
#include "application/object/object_bg.h"

static const D3DXVECTOR2 MOVE_FAR(0.00005f,0.0006f);
static const D3DXVECTOR2 MOVE_NEAR(0.0001f,0.001f);

//=============================================================================
// constructor
//=============================================================================
GameBg::GameBg(void)
:game_bg_far_(nullptr)
,game_bg_near_(nullptr)
,position_(0.0f,0.0f)
,old_position_(0.0f,0.0f)
,move_(0.0f, 0.0f)
{
}

//=============================================================================
// destructor
//=============================================================================
GameBg::~GameBg(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool GameBg::Initialize(void)
{
	game_bg_far_ = new ObjectBg();
	game_bg_far_->Initialize();

	game_bg_near_ = new ObjectBg();
	game_bg_near_->Initialize();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void GameBg::Uninitialize(void)
{
	SafeRelease(game_bg_far_);
	SafeRelease(game_bg_near_);
}

//=============================================================================
// update
//=============================================================================
void GameBg::Update(void)
{
	D3DXVECTOR2 move_far = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 move_near = D3DXVECTOR2(0.0f, 0.0f);

	if(position_.y < old_position_.y)
	{
		move_far.y = -MOVE_FAR.y;
		move_near.y = -MOVE_NEAR.y;
	}
	else if(position_.y > old_position_.y)
	{
		move_far.y = MOVE_FAR.y;
		move_near.y = MOVE_NEAR.y;
	}
	if(position_.x != old_position_.x)
	{
		move_far.x = move_.x * MOVE_FAR.x;
		move_near.x = move_.x * MOVE_NEAR.x;
	}

	game_bg_far_->__Set_move(move_far);
	game_bg_near_->__Set_move(move_near);

	game_bg_far_->Update();
	game_bg_near_->Update();
}

//=============================================================================
// draw
//=============================================================================
void GameBg::Draw(void)
{
	game_bg_far_->Draw();
	game_bg_near_->Draw();

}

//=============================================================================
//ステージ教える
//=============================================================================
void GameBg::__SetTexture(Stage::TYPE type)
{
	switch(type)
	{
	case Stage::TYPE_TUTORIAL:
	default:
		game_bg_far_->__SetTexture(Texture::TEXTURE_ID_GAME_BG_FAR_000);
		game_bg_near_->__SetTexture(Texture::TEXTURE_ID_GAME_BG_NEAR_000);
		break;
		
	case Stage::TYPE_STAGE1:
		game_bg_far_->__SetTexture(Texture::TEXTURE_ID_GAME_BG_FAR_001);
		game_bg_near_->__SetTexture(Texture::TEXTURE_ID_GAME_BG_NEAR_001);
		break;

	case Stage::TYPE_STAGE2:
		game_bg_far_->__SetTexture(Texture::TEXTURE_ID_GAME_BG_FAR_002);
		game_bg_near_->__SetTexture(Texture::TEXTURE_ID_GAME_BG_NEAR_002);
		break;
	}
}

void GameBg::ReSetUv(void)
{
	game_bg_far_->ReSetUv();
	game_bg_near_->ReSetUv();
}




//---------------------------------- EOF --------------------------------------
