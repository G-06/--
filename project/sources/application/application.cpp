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
#include "object/option.h"

//=============================================================================
// constructor
//=============================================================================
Application::Application(void)
	:scene_manager_(nullptr)
	,frame_controller_(nullptr)
	,is_loop_(false)
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
		Uninitialize();
		ASSERT("failed initialize scene manager");
		return false;
	}

	// create frame controller
	frame_controller_ = new FrameController();

	// initialize frame controller
	if(!SafeInitialize(frame_controller_))
	{
		Uninitialize();
		ASSERT("failed initialize frame controller");
	}

	//GET_DIRECT_INPUT->RegisterInputEventVertual(INPUT_EVENT_VIRTUAL_LEFT,INPUT_EVENT_LEFT);
	//GET_DIRECT_INPUT->RegisterInputEventVertual(INPUT_EVENT_VIRTUAL_RIGHT,INPUT_EVENT_RIGHT);
	//GET_DIRECT_INPUT->RegisterInputEventVertual(INPUT_EVENT_VIRTUAL_UP,INPUT_EVENT_UP);
	//GET_DIRECT_INPUT->RegisterInputEventVertual(INPUT_EVENT_VIRTUAL_DOWN,INPUT_EVENT_DOWN);
	//
	//GET_DIRECT_INPUT->RegisterInputEventVertual(INPUT_EVENT_VIRTUAL_LEFT,INPUT_EVENT_PAD_L_LEFT);
	//GET_DIRECT_INPUT->RegisterInputEventVertual(INPUT_EVENT_VIRTUAL_RIGHT,INPUT_EVENT_PAD_L_RIGHT);
	//GET_DIRECT_INPUT->RegisterInputEventVertual(INPUT_EVENT_VIRTUAL_UP,INPUT_EVENT_PAD_L_UP);
	//GET_DIRECT_INPUT->RegisterInputEventVertual(INPUT_EVENT_VIRTUAL_DOWN,INPUT_EVENT_PAD_L_DOWN);
	//
	//GET_DIRECT_INPUT->RegisterInputEventVertual(INPUT_EVENT_VIRTUAL_LEFT,INPUT_EVENT_PAD_2);
	//GET_DIRECT_INPUT->RegisterInputEventVertual(INPUT_EVENT_VIRTUAL_RIGHT,INPUT_EVENT_PAD_3);
	//GET_DIRECT_INPUT->RegisterInputEventVertual(INPUT_EVENT_VIRTUAL_UP,INPUT_EVENT_PAD_0);
	//GET_DIRECT_INPUT->RegisterInputEventVertual(INPUT_EVENT_VIRTUAL_DOWN,INPUT_EVENT_PAD_1);
	//
	//GET_DIRECT_INPUT->RegisterInputEventVertual(INPUT_EVENT_VIRTUAL_CANCEL,INPUT_EVENT_Z);
	//GET_DIRECT_INPUT->RegisterInputEventVertual(INPUT_EVENT_VIRTUAL_CANCEL,INPUT_EVENT_PAD_5);
	//
	//GET_DIRECT_INPUT->RegisterInputEventVertual(INPUT_EVENT_VIRTUAL_6,INPUT_EVENT_X);
	//GET_DIRECT_INPUT->RegisterInputEventVertual(INPUT_EVENT_VIRTUAL_6,INPUT_EVENT_PAD_9);
	//
	//GET_DIRECT_INPUT->RegisterInputEventVertual(INPUT_EVENT_VIRTUAL_7,INPUT_EVENT_RETURN);
	//GET_DIRECT_INPUT->RegisterInputEventVertual(INPUT_EVENT_VIRTUAL_7,INPUT_EVENT_PAD_6);
	//
	//GET_DIRECT_INPUT->RegisterInputEventVertual(INPUT_EVENT_VIRTUAL_8,INPUT_EVENT_P);
	//GET_DIRECT_INPUT->RegisterInputEventVertual(INPUT_EVENT_VIRTUAL_8,INPUT_EVENT_PAD_13);
	//
	//GET_DIRECT_INPUT->SaveInputEventVertual();
	
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
		is_loop_ = false;
	}

	if(scene_manager_->__is_stop())
	{
		is_loop_ = false;
	}

	frame_controller_->Wait();
}

//---------------------------------- EOF --------------------------------------
