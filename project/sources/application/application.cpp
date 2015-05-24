//*****************************************************************************
//
// application
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "application.h"
#include "system/system.h"
#include "scene/scene_manager.h"
#include "frame/frame_controller.h"

//=============================================================================
// constructor
//=============================================================================
Application::Application(void) :
scene_manager_(nullptr),
is_loop_(false)
{
}

//=============================================================================
// destructor
//=============================================================================
Application::~Application(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool Application::Initialize(void)
{
	// is loop
	is_loop_ = true;

	// create scene manager
	scene_manager_ = new SceneManager();

	// initialize scene manager
	if(!SafeInitialize(scene_manager_))
	{
		SafeRelease(scene_manager_);
		ASSERT("failed initialize scene manager");
		return false;
	}

	// create frame controller
	frame_controller_ = new FrameController();

	// initialize frame controller
	if(!SafeInitialize(frame_controller_))
	{
		SafeRelease(scene_manager_);
		SafeRelease(frame_controller_);
		ASSERT("failed initialize frame controller");
	}

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void Application::Uninitialize(void)
{
	is_loop_ = false;

	// release scene manager
	SafeRelease(scene_manager_);

	// release frame controller
	SafeRelease(frame_controller_);

}

//=============================================================================
// update
//=============================================================================
void Application::Update(void)
{
	// update frame controller
	frame_controller_->Update();

	// print fps
	DEBUG_TOOL.__debug_display()->Print("FPS : %d\n",frame_controller_->__fps());

	// is loop window system
	if(!GET_SYSTEM.__window()->__is_loop())
	{
		is_loop_ = false;
	}

	// update direct input
	GET_DIRECT_INPUT->Update();

	// update xaudio2
	GET_XAUDIO2->Update();

	// update debug tool
	DEBUG_TOOL.Update();

	if(!DEBUG_TOOL.__is_pause())
	{
		// update scene manager
		scene_manager_->Update();
	}

	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_LSHIFT))
	{
		GET_BGM->Play(BGM::BGM_ID_TEST);
	}

	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_RSHIFT))
	{
		GET_BGM->Play(BGM::BGM_ID_TEST2);
	}

	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_SPACE))
	{
		GET_BGM->Stop();
	}

	if(GET_SYSTEM.__directx9()->BeginDraw())
	{
		// draw scene manager
		scene_manager_->Draw();

		if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_0))
		{
			GET_DIRECTX9->ScreenShot();
			DEBUG_TOOL.__debug_trace()->Print("capture screen shot\n");
		}

		// draw debug tool
		DEBUG_TOOL.Draw();

		GET_SYSTEM.__directx9()->EndDraw();
	}

	if(scene_manager_->__is_error())
	{
		is_loop_ = true;
	}

	frame_controller_->Wait();
}

//---------------------------------- EOF --------------------------------------
