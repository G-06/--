//*****************************************************************************
//
// scene manager
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "scene_manager.h"
#include "scene.h"
#include "factory/scene_factory.h"
#include "render/fade.h"

//=============================================================================
// constructor
//=============================================================================
SceneManager::SceneManager(void)
	:current_scene_(nullptr)
	,next_scene_(nullptr)
	,is_error_(false)
{
}

//=============================================================================
// destructor
//=============================================================================
SceneManager::~SceneManager(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool SceneManager::Initialize(void)
{
	// create current scene
	current_scene_ = new SceneLogo();

	// initialize current scene
	if(!SafeInitialize(current_scene_))
	{
		return false;
	}

	// create fade
	fade_ = new Fade();

	// initialize fade
	fade_->Initialize();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void SceneManager::Uninitialize(void)
{
	// release current scene
	SafeRelease(current_scene_);

	// release next scene
	SafeRelease(next_scene_);

	// release fade
	SafeRelease(fade_);
}

//=============================================================================
// update
//=============================================================================
void SceneManager::Update(void)
{
	// is next scene
	if(next_scene_ != nullptr && fade_->__type() == Fade::TYPE_FADE)
	{
		// change next scene
		SafeRelease(current_scene_);
		current_scene_ = next_scene_;
		next_scene_ = nullptr;
		fade_->Start(Fade::TYPE_IN);
	}

	if(fade_->__type() == Fade::TYPE_NONE)
	{
		current_scene_->__is_fade(false);
	}
	else
	{
		current_scene_->__is_fade(true);
	}

	// update current scene
	current_scene_->Update();

	// is next scene factory
	if(current_scene_->__next_scene_factory() != nullptr && fade_->__type() == Fade::TYPE_NONE)
	{
		// fade out
		fade_->Start(Fade::TYPE_OUT);
		next_scene_ = current_scene_->__next_scene_factory()->Create();

		if(!SafeInitialize(next_scene_))
		{
			is_error_ = true;
			DEBUG_TOOL.__debug_trace()->Print("failed initialize next scene\n");
			return;
		}
	}

	// update fade
	fade_->Update();
}

//=============================================================================
// draw
//=============================================================================
void SceneManager::Draw(void)
{
	// draw current scene
	current_scene_->Draw();

	// draw fade
	fade_->Draw();
}

//---------------------------------- EOF --------------------------------------
