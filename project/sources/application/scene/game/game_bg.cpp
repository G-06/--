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

static const D3DXVECTOR2 MOVE_X_FAR(0.002f,0.0f);
static const D3DXVECTOR2 MOVE_Y_FAR(0.0f,0.0006f);

static const D3DXVECTOR2 MOVE_X_NEAR(0.004f,0.0f);
static const D3DXVECTOR2 MOVE_Y_NEAR(0.0f,0.0008f);

//=============================================================================
// constructor
//=============================================================================
GameBg::GameBg(void)
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

	position_ = D3DXVECTOR2(0.0f,0.0f);
	old_position_ = D3DXVECTOR2(0.0f,0.0f);

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
	//”wŒi“®‚©‚·‚æ
	if((position_.x != old_position_.x)||(position_.y != old_position_.y))
	{
		if(position_.x < old_position_.x)
		{
			game_bg_far_->__Set_move(-MOVE_X_FAR);
			game_bg_near_->__Set_move(-MOVE_X_NEAR);
		}
		else if(position_.x > old_position_.x)
		{
			game_bg_far_->__Set_move(MOVE_X_FAR);
			game_bg_near_->__Set_move(MOVE_X_NEAR);
		}
		if(position_.y < old_position_.y)
		{
			game_bg_far_->__Set_move(-MOVE_Y_FAR);
			game_bg_near_->__Set_move(-MOVE_Y_NEAR);

		}
		else if(position_.y > old_position_.y)
		{
			game_bg_far_->__Set_move(MOVE_Y_FAR);
			game_bg_near_->__Set_move(MOVE_Y_NEAR);
		}
	game_bg_far_->Update();
	game_bg_near_->Update();
	}

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
//ƒXƒe[ƒW‹³‚¦‚é
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
