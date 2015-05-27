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

#define TIME			(120)			//ロゴが表示されてから切り替わるまで
#define DELAY			(TIME+5)				//中割の表示時間
#define GO_TITLE		(TIME+DELAY+30)	//タイトルに行く時間

#define DEFAULT_POS_X	(400.0f)		//ロゴ位置
#define DEFAULT_POS_Y	(200.0f)

#define DEFAULT_SIZE_X	(400.0f)		//ロゴサイズ
#define DEFAULT_SIZE_Y	(400.0f)

#define DIVISION_X		(3)				//ロゴ枚数
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

	logo_timer_=0;
	next_scene_flag_ = false;
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
	else if(logo_timer_ == DELAY)
	{
		logo_neko_->__index(2);
		logo_neko_->SetParameter();
	}
	else if(logo_timer_ == GO_TITLE)
	{
		next_scene_flag_ = true;
	}

	logo_timer_++;
}

//=============================================================================
// draw
//=============================================================================
void Logo::Draw(void)
{
	logo_neko_->Draw();
}

//---------------------------------- EOF --------------------------------------
