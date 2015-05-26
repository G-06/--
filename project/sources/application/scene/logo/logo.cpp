//*****************************************************************************
//
// title bg
//
// Author		: taichi kitazawa
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "logo.h"
#include "render/sprite.h"
#include "system/system.h"

#define TIME	(80)
#define DELAY	(5)

#define DEFAULT_POS_X	(400.0f)
#define DEFAULT_POS_Y	(200.0f)

#define DEFAULT_SIZE_X	(400.0f)
#define DEFAULT_SIZE_Y	(400.0f)

#define DIVISION_X		(3)
#define DIVISION_Y		(1)

//=============================================================================
// constructor
//=============================================================================
Logo::Logo(void)
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
	logo_neko_->Initialize();
	logo_neko_->__size(D3DXVECTOR2(DEFAULT_SIZE_X,DEFAULT_SIZE_Y));
	logo_neko_->__position(D3DXVECTOR2(DEFAULT_POS_X,DEFAULT_POS_Y));
	logo_neko_->__texture_id(Texture::TEXTURE_ID_LOGO);
	logo_neko_->__division_height(DIVISION_Y);
	logo_neko_->__division_width(DIVISION_X);
	logo_neko_->__index((u32)0);
	logo_neko_->SetParameter();


	index_num_=99;
	logo_timer_=0;
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void Logo::Uninitialize(void)
{
	SafeRelease(logo_neko_);
	SafeDelete(logo_neko_);
}

//=============================================================================
// update
//=============================================================================
void Logo::Update(void)
{
	if(logo_timer_ == TIME)
	{
		logo_neko_->__index(1);
		logo_neko_->SetParameter();
	}
	if(logo_timer_ == TIME+DELAY)
	{
		logo_neko_->__index(2);
		logo_neko_->SetParameter();
	}
	else
	{
		logo_timer_++;
	}

	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_SPACE))
	{
		logo_timer_=0;
		logo_neko_->__index((u32)0);
		logo_neko_->SetParameter();
	}

}

//=============================================================================
// draw
//=============================================================================
void Logo::Draw(void)
{
	logo_neko_->Draw();
}

//---------------------------------- EOF --------------------------------------
