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

// HACK
#include "system\xaudio2\xaudio2.h"

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
		ASSERT("failed initialize scene manager");
		return false;
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
}

//=============================================================================
// update
//=============================================================================
void Application::Update(void)
{
	FrameController* frame_controller = new FrameController();
	frame_controller->Initialize();
	XAudio2* xaudio2 = new XAudio2();

	xaudio2->Initialize();

	XAudio2Sound* xaudio2_sound = xaudio2->CreateXAudio2Sound();

	xaudio2_sound->LoadFromFile("resources/bgm/test.wav");

	xaudio2_sound->Play(0);

	f32 volume = 1.0f;
	f32 master_volume = 1.0f;

	while(is_loop_)
	{
		// update frame controller
		frame_controller->Update();

		// print fps
		DEBUG_TOOL.__debug_display()->Print("FPS : %d\n",frame_controller->__fps());

		// is loop window system
		if(!GET_SYSTEM.__window()->__is_loop())
		{
			is_loop_ = false;
		}

		// update direct input
		GET_DIRECT_INPUT->Update();

		// update debug tool
		DEBUG_TOOL.Update();

		if(!DEBUG_TOOL.__is_pause())
		{
			// update scene manager
			scene_manager_->Update();
		}

		master_volume = xaudio2->__volume();
		volume = xaudio2_sound->__volume();

		DEBUG_TOOL.__debug_display()->Print("Volume : %f\n",volume);
		DEBUG_TOOL.__debug_display()->Print("Master Volume : %f\n",master_volume);

		if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_UP))
		{
			volume += 0.1f;
		}

		if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_DOWN))
		{
			volume -= 0.1f;
		}

		if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_LEFT))
		{
			master_volume -= 0.1f;
		}

		if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_RIGHT))
		{
			master_volume += 0.1f;
		}

		xaudio2_sound->SetVolume(volume);
		xaudio2->SetMasterVolume(master_volume);

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

		frame_controller->Wait();
	}

	SafeRelease(xaudio2_sound);
	SafeRelease(xaudio2);
	SafeRelease(frame_controller);
}

//---------------------------------- EOF --------------------------------------
