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
#include "title_select.h"
#include "object/message_window.h"
#include "system/system.h"
#include "system/directx9/texture/texture.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const u32 SceneTitle::GO_LOGO_FRAME = 600;		//ƒƒS‚É–ß‚é‚Ü‚Å‚ÌŽžŠÔ

// select position
const f32 SELECT_OFFSET_Y = 100.0f;
const D3DXVECTOR2 SELECT_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f, 450.0f);

// string texture_id
const Texture::TEXTURE_ID SELECT_STRING_TEXTURE[] = {
	Texture::TEXTURE_ID_TITLE_STRING_TEST_A,
	Texture::TEXTURE_ID_TITLE_STRING_TEST_A,
	Texture::TEXTURE_ID_TITLE_STRING_TEST_A };

//=============================================================================
// constructor
//=============================================================================
SceneTitle::SceneTitle(void)
	:Scene(TYPE_TITLE)
	,title_bg_(nullptr)
	,title_logo_(nullptr)
	,message_window_(nullptr)
	,frame_count_(0)
	,current_select_(0)
{
	memset(title_select_, 0, sizeof(title_select_));
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

	for(int i = 0 ; i < SELECT_MAX ; i++){
		title_select_[i].frame_ = new TitleSelect();
		title_select_[i].select_ = new TitleSelect();
		title_select_[i].frame_->Initialize();
		title_select_[i].select_->Initialize();

		// texture
		title_select_[i].select_->__texture_id(SELECT_STRING_TEXTURE[i]);

		// position
		const D3DXVECTOR2 position = D3DXVECTOR2(SELECT_POSITION.x, SELECT_POSITION.y + (i * SELECT_OFFSET_Y));
		title_select_[i].frame_->__position(position);
		title_select_[i].select_->__position(position);
	}
	title_select_[current_select_].frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_001);

	// message_window
	message_window_ = new MessageWindow();
	message_window_->Initialize();
	message_window_->__dest_frame_count(25);

	frame_count_ = 0;
	current_select_ = 0;

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void SceneTitle::Uninitialize(void)
{
	SafeRelease(title_bg_);

	SafeRelease(title_logo_);

	for(int i = 0 ; i < SELECT_MAX ; i++){
		SafeRelease(title_select_[i].frame_);
		SafeRelease(title_select_[i].select_);
	}

	SafeRelease(message_window_);

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

		// select
		bool input = false;
		const s32 oldSelect = current_select_;
		if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_UP)){
			current_select_--;
			input = true;
			if(current_select_ < 0) current_select_ = SELECT_MAX - 1;
		}
		else if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_DOWN)){
			current_select_++;
			input = true;
			if(current_select_ >= SELECT_MAX) current_select_ = 0;
		}

		if(input){
			frame_count_ = 0;
			title_select_[oldSelect].frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_000);
			title_select_[current_select_].frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_001);
		} // select


		// message
		if(message_window_->__is_move() == false){

			if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_SPACE)){
			frame_count_ = 0;
				if(message_window_->__is_show()){
					message_window_->Close();
				}else{
					message_window_->Show();
				}
			}

			//
			if(message_window_->__is_show()){
				
//				const s32 old_select = message_window_->__is_select();

				if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_LEFT)){
					message_window_->SelectDown();
				}
				if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_RIGHT)){
					message_window_->SelectUp();
				}
			}
		}


		message_window_->Update();
	}
}

//=============================================================================
// draw
//=============================================================================
void SceneTitle::Draw(void)
{
	title_bg_->Draw();
	title_logo_->Draw();
	for(int i = 0 ; i < SELECT_MAX ; i++){
		title_select_[i].frame_->Draw();
		title_select_[i].select_->Draw();
	}

	message_window_->Draw();
}

//=============================================================================
// create factory
//=============================================================================
SceneFactory* SceneTitle::CreateFactory(void)const
{
	return new TitleFactory();
}

//---------------------------------- EOF --------------------------------------
