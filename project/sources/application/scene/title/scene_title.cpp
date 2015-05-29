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
#include "title_logo.h"
#include "system/system.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const u32 SceneTitle::GO_LOGO_FRAME = 600;		//ƒƒS‚É–ß‚é‚Ü‚Å‚ÌŽžŠÔ

//=============================================================================
// constructor
//=============================================================================
SceneTitle::SceneTitle(void)
	:Scene(TYPE_TITLE)
	,title_bg_(nullptr)
	,title_logo_(nullptr)
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

	title_logo_ = new TitleLogo();
	title_logo_->Initialize();
	frame_count_ = 0;

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void SceneTitle::Uninitialize(void)
{
	SafeRelease(title_bg_);

	SafeRelease(title_logo_);

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
	title_logo_->Draw();
}

//=============================================================================
// create factory
//=============================================================================
SceneFactory* SceneTitle::CreateFactory(void)const
{
	return new TitleFactory();
}

//---------------------------------- EOF --------------------------------------
