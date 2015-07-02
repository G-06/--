//*****************************************************************************
//
// logo
//
// Author		: taichi kitazawa
//				: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "logo.h"
#include "render/sprite.h"
#include "system/system.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 Logo::DEFAULT_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f,DEFAULT_SCREEN_HEIGHT * 0.5f);
const D3DXVECTOR2 Logo::DEFAULT_SIZE = D3DXVECTOR2(512.0f,512.0f);
const u32 Logo::DEFAULT_DIVISION_WIDTH = 3;
const u32 Logo::DEFAULT_DIVISION_HEIGHT = 1;
const Animation::DATA Logo::ANIMATION_DATA[] =
{
	Animation::DATA(5,1,0),
	Animation::DATA(5,2,1),
	Animation::DATA(5,2,2),
};

//=============================================================================
// constructor
//=============================================================================
Logo::Logo(void)
	:logo_neko_(nullptr)
	,animation_(nullptr)
	,is_end_(false)
	,is_active_(false)
{
}

//=============================================================================
// destructor
//=============================================================================
Logo::~Logo(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool Logo::Initialize(void)
{
	logo_neko_ = new Sprite();

	if(!SafeInitialize(logo_neko_))
	{
		return false;
	}

	logo_neko_->__size(DEFAULT_SIZE);
	logo_neko_->__position(DEFAULT_POSITION);
	logo_neko_->__texture_id(Texture::TEXTURE_ID_TEAM_LOGO);
	logo_neko_->__division_width(DEFAULT_DIVISION_WIDTH);
	logo_neko_->__division_height(DEFAULT_DIVISION_HEIGHT);
	logo_neko_->__index((u32)0);
	logo_neko_->__point(Sprite::POINT_CENTER);
	logo_neko_->SetParameter();

	animation_ = new Animation();

	if(!SafeInitialize(animation_))
	{
		return false;
	}

	animation_->Add(ANIMATION_DATA,sizeof(ANIMATION_DATA) / sizeof(Animation::DATA));

	is_end_ = false;

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void Logo::Uninitialize(void)
{
	SafeRelease(logo_neko_);
	SafeRelease(animation_);
}

//=============================================================================
// update
//=============================================================================
void Logo::Update(void)
{
	animation_->Update();

	logo_neko_->__index(animation_->__current_index());
	logo_neko_->SetParameter();

	if(animation_->__is_end())
	{
		is_end_ = true;
	}
}

//=============================================================================
// draw
//=============================================================================
void Logo::Draw(void)
{
	logo_neko_->Draw();
}

//=============================================================================
// start
//=============================================================================
void Logo::Start(void)
{
	animation_->Start(0);
	is_end_ = false;
	is_active_ = true;
}

//---------------------------------- EOF --------------------------------------
