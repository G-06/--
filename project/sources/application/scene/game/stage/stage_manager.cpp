//*****************************************************************************
//
// stage manager
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "stage_manager.h"
#include "stage.h"
#include "stage_factory.h"
#include "render/fade.h"

//=============================================================================
// constructor
//=============================================================================
StageManager::StageManager(void)
	:current_stage_(nullptr)
	,next_stage_(nullptr)
	,is_error_(false)
{
}

//=============================================================================
// destructor
//=============================================================================
StageManager::~StageManager(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool StageManager::Initialize(void)
{
	// create current stage
	current_stage_ = new StageSelect();

	// initialize current stage
	if(!SafeInitialize(current_stage_))
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
void StageManager::Uninitialize(void)
{
	// release current stage
	SafeRelease(current_stage_);

	// release next stage
	SafeRelease(next_stage_);

	// release fade
	SafeRelease(fade_);
}

//=============================================================================
// update
//=============================================================================
void StageManager::Update(void)
{
	// is next stage
	if(next_stage_ != nullptr && fade_->__type() == Fade::TYPE_FADE)
	{
		// change next stage
		SafeRelease(current_stage_);
		current_stage_ = next_stage_;
		next_stage_ = nullptr;
		fade_->Start(Fade::TYPE_IN);
	}

	if(fade_->__type() == Fade::TYPE_NONE)
	{
		current_stage_->__is_fade(false);
	}
	else
	{
		current_stage_->__is_fade(true);
	}

	// update current stage
	current_stage_->Update();

	// is next stage factory
	if(current_stage_->__next_stage_factory() != nullptr && fade_->__type() == Fade::TYPE_NONE)
	{
		// fade out
		fade_->Start(Fade::TYPE_OUT);
		next_stage_ = current_stage_->__next_stage_factory()->Create();

		if(!SafeInitialize(next_stage_))
		{
			is_error_ = true;
			DEBUG_TOOL.__debug_trace()->Print("failed initialize next stage\n");
			return;
		}
	}

	// update fade
	fade_->Update();
}

//=============================================================================
// draw
//=============================================================================
void StageManager::Draw(void)
{
	// draw current stage
	current_stage_->Draw();

	// draw fade
	fade_->Draw();
}

//---------------------------------- EOF --------------------------------------
