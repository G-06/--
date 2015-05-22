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
#include "common/animation/animation.h"
#include "render/text_box.h"
#include "object/stage_offset.h"
#include "object\stage.h"

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

	Animation::DATA data[] =
	{
		Animation::DATA(4,1,0),
		Animation::DATA(2,2,1),
		Animation::DATA(1,3,2),
		Animation::DATA(2,4,3),
		Animation::DATA(4,5,4),
		Animation::DATA(2,6,5),
		Animation::DATA(1,7,6),
		Animation::DATA(2,8,7),
		Animation::DATA(4,9,8),
		Animation::DATA(2,0,9)
	};
	animation_ = new Animation();
	animation_->Add(data,sizeof(data) / sizeof(Animation::DATA));
	animation_->Start(0);

	position_ = D3DXVECTOR2(0.0f,0.0f);
	sprite_ = new Sprite();
	sprite_->Initialize();
	sprite_->__size(D3DXVECTOR2(100.0f,100.0f));
	sprite_->__division_width(5);
	sprite_->__division_height(2);
	sprite_->__index(0);
	sprite_->__texture_id(Texture::TEXTURE_ID_ANIM_TEST);
	sprite_->SetParameter();

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

	stage_ = new Stage();
	stage_->Initialize();

	stage_offset_ = new StageOffset();
	stage_offset_->Initialize();
	stage_offset_->__stage_size(stage_->__size());
	stage_offset_->__screen_size(D3DXVECTOR2((f32)DEFAULT_SCREEN_WIDTH,(f32)DEFAULT_SCREEN_HEIGHT));

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
	SafeRelease(animation_);
	SafeRelease(sprite_);
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

			if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_A))
				position_.x -= 3.0f;
			if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_D))
				position_.x += 3.0f;

			if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_SPACE))
			{
				sprite_->__is_flip(!sprite_->__is_flip());
			}

			stage_offset_->__reference_position(position_);
			stage_offset_->Update();
			D3DXVECTOR2 position = stage_offset_->__position();
			animation_->Update();
			sprite_->__index(animation_->__number());
			sprite_->__position(D3DXVECTOR2(position_.x - position.x,position_.y - position.y));
			stage_->__offset_position(position);
			stage_->Update();
			sprite_->SetParameter();

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
			stage_->Draw();
			text_box_->Draw();

			sprite_->Draw();

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
