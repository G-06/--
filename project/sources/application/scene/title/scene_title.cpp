//*****************************************************************************
//
// scene title
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "scene_title.h"
#include "scene/factory/scene_factory.h"
#include "title_bg.h"
#include "system/system.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const u32 SceneTitle::GO_LOGO_FRAME = 600;		//ロゴに戻るまでの時間

//=============================================================================
// constructor
//=============================================================================
SceneTitle::SceneTitle(void)
	:Scene(TYPE_TITLE)
	,title_bg_(nullptr)
	,frame_count_(0)
{
}

//=============================================================================
// destructor
//=============================================================================
SceneTitle::~SceneTitle(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool SceneTitle::Initialize(void)
{
	title_bg_ = new TitleBg();
	title_bg_->Initialize();

	frame_count_ = 0;

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void SceneTitle::Uninitialize(void)
{
	SafeRelease(title_bg_);

	SafeDelete(next_scene_factory_);
}

//=============================================================================
// update
//=============================================================================
void SceneTitle::Update(void)
{
	if(is_fade_)
	{
	}
	else
	{
		frame_count_++;

		if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_7) || GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_8))
		{
			if(next_scene_factory_ == nullptr)
			{
				next_scene_factory_ = new GameFactory();
			}
		}

		if(frame_count_ >= GO_LOGO_FRAME)
		{
			if(next_scene_factory_ == nullptr)
			{
				next_scene_factory_ = new LogoFactory();
			}
		}
	}
}

//=============================================================================
// draw
//=============================================================================
void SceneTitle::Draw(void)
{
	title_bg_->Draw();
}

//=============================================================================
// create factory
//=============================================================================
SceneFactory* SceneTitle::CreateFactory(void)const
{
	return new TitleFactory();
}

//---------------------------------- EOF --------------------------------------
