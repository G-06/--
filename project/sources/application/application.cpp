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
#include "system/directx9/font/font_texture.h"
#include "render/sprite.h"
#include "render/text_box.h"

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

	//GET_DIRECT_INPUT->RegisterInputEventVertual(INPUT_EVENT_VIRTUAL_0,INPUT_EVENT_R);

	text_box_ = new TextBox(FontTexture::TYPE_MS_GOTHIC,32);
	text_box_->Initialize();

	text_box_->Print("フォントのテストです\n");
	text_box_->Print("次の事を確認して下さい\n");
	text_box_->Print("方向キーによる移動\n",D3DXCOLOR(1.0f,1.0f,0.0f,1.0f));
	text_box_->Print("文字列に抜けが無いか\n");
	text_box_->__font_color(D3DXCOLOR(1.0f,0.0f,1.0f,1.0f));
	text_box_->Print("終了後のメモリーリーク\n");
	text_box_->Print("Rキーでリセットされるか\n");
	text_box_->Print("座標はリセットされません\n");

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

	SafeRelease(text_box_);
}

//=============================================================================
// update
//=============================================================================
void Application::Update(void)
{
	FrameController* frame_controller = new FrameController();
	frame_controller->Initialize();

	while(is_loop_)
	{
		// update frame controller
		frame_controller->Update();

		// is loop window system
		if(!GET_SYSTEM.__window()->__is_loop())
		{
			is_loop_ = false;
		}

		// update direct input
		GET_DIRECT_INPUT->Update();

		// update debug tool
		DEBUG_TOOL.Update();

		// print fps
		DEBUG_TOOL.__debug_display()->Print("FPS : %d\n",frame_controller->__fps());

		if(!DEBUG_TOOL.__is_pause())
		{
			// update scene manager
			scene_manager_->Update();

			if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_LEFT))
			{
				text_box_->__position(D3DXVECTOR2(text_box_->__position().x - 1.0f,text_box_->__position().y));
			}

			if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_RIGHT))
			{
				text_box_->__position(D3DXVECTOR2(text_box_->__position().x + 1.0f,text_box_->__position().y));
			}

			if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_UP))
			{
				text_box_->__position(D3DXVECTOR2(text_box_->__position().x,text_box_->__position().y - 1.0f));
			}

			if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_DOWN))
			{
				text_box_->__position(D3DXVECTOR2(text_box_->__position().x,text_box_->__position().y + 1.0f));
			}

			if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_VIRTUAL_0))
			{
				text_box_->Restart();
			}
		}

		if(GET_SYSTEM.__directx9()->BeginDraw())
		{
			// draw scene manager
			scene_manager_->Draw();

			text_box_->Draw();

			if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_0))
			{
				GET_DIRECTX9->ScreenShot();
				DEBUG_TOOL.__debug_console()->Print("capture screen shot\n");
			}

			// draw debug tool
			DEBUG_TOOL.Draw();

			GET_SYSTEM.__directx9()->EndDraw();
		}

		frame_controller->Wait();
	}

	SafeRelease(frame_controller);
}

//---------------------------------- EOF --------------------------------------
