//*****************************************************************************
//
// scene logo
//
// Author		: taichi kitazawa
//				: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "scene_logo.h"
#include "logo.h"
#include "logo_bg.h"
#include "scene/factory/scene_factory.h"
#include "system/system.h"


//=============================================================================
// constant definition
//=============================================================================
const u32 START_FRAME_COUNT = 40;
const u32 END_FRAME_COUNT = 60;

//=============================================================================
// constructor
//=============================================================================
SceneLogo::SceneLogo(void)
	:Scene(TYPE_LOGO)
	,logo_neko_(nullptr)
	,logo_bg_(nullptr)
	,frame_count_(0)
	,end_count_(0)
{
}

//=============================================================================
// destructor
//=============================================================================
SceneLogo::~SceneLogo(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool SceneLogo::Initialize(void)
{
	logo_neko_ = new Logo;

	if(!SafeInitialize(logo_neko_))
	{
		return false;
	}

	logo_bg_ = new LogoBg;

	if(!SafeInitialize(logo_bg_))
	{
		return false;
	}

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void SceneLogo::Uninitialize(void)
{
	SafeRelease(logo_neko_);
	SafeRelease(logo_bg_);
	SafeDelete(next_scene_factory_);
}

//=============================================================================
// update
//=============================================================================
void SceneLogo::Update(void)
{
	if(is_fade_)
	{
	}
	else
	{
		frame_count_++;

		const u32 START_FRAME_COUNT = 45;
		if(frame_count_ >= START_FRAME_COUNT){
			if(!logo_neko_->__is_active())
			{
				logo_neko_->Start();
			}

			logo_neko_->Update();
			logo_bg_->Update();

			//タイトルに行くタイミングを見計らっている
			if(logo_neko_->__is_end() )
			{
				end_count_++;
				if( end_count_ > END_FRAME_COUNT ){
					if(next_scene_factory_ == nullptr)
					{
						next_scene_factory_ = new TitleFactory();
					}
				}
			}
		}
	}
}

//=============================================================================
// draw
//=============================================================================
void SceneLogo::Draw(void)
{
	// draw stage
	logo_bg_->Draw();
	logo_neko_->Draw();
}

//=============================================================================
// create factory
//=============================================================================
SceneFactory* SceneLogo::CreateFactory(void)const
{
	return new LogoFactory();
}

//---------------------------------- EOF --------------------------------------
