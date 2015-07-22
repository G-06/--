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
#include "title_push_start.h"
#include "title_luminescence.h"
#include "title_circle.h"
#include "title_select.h"
#include "object/message_window.h"
#include "system/system.h"
#include "system/directx9/texture/texture.h"
#include "object/option.h"


//*****************************************************************************
// constant definition
//*****************************************************************************
const u32 SceneTitle::GO_LOGO_FRAME = 60 * 30;	// ロゴに戻るまでの時間
const u32 DEST_FRAME_COUNT = 20;				// ウィンドウ開閉の時間
const u32 DESIDE_INTERVAL_COUNT = 30;			// 決定ボタン後の余韻

// push_startの点滅数値
const f32 PUSH_START_ALPHA_MAX = 1.25f;
const f32 PUSH_START_ALPHA_MIN = 0.0f;
const f32 PUSH_START_SCALE = 0.9f;
const D3DXVECTOR2 PUSH_START_SIZE = D3DXVECTOR2(256 * PUSH_START_SCALE, 64.0f * PUSH_START_SCALE);

// luminesceneの点滅数値
const f32 LUMINESCENCE_ALPHA_MAX = 1.1f;
const f32 LUMINESCENCE_ALPHA_MIN = 0.15f;

// circleの回転
const f32 CIRCLE_ROTATION = 0.005f;

// select position
const f32 SELECT_OFFSET_Y = 85.0f;
const D3DXVECTOR2 SELECT_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f, 485.0f);

// color
const D3DXCOLOR DEFAULT_COLOR = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

// frame size
const f32 FRAME_SCALE = 0.9f;
const D3DXVECTOR2 FRAME_SIZE = D3DXVECTOR2(324.0f * FRAME_SCALE,71.0f * FRAME_SCALE);
const f32 PUSH_SIZE_SCALE = 1.1f;
const D3DXVECTOR2 PUSH_FRAME_SIZE = D3DXVECTOR2(324.0f * PUSH_SIZE_SCALE,71.0f * PUSH_SIZE_SCALE);

// string texture_id
const Texture::TEXTURE_ID SELECT_STRING_TEXTURE[] = {
	Texture::TEXTURE_ID_TITLE_STRING_GAME_START,
	Texture::TEXTURE_ID_TITLE_STRING_OPTION,
	Texture::TEXTURE_ID_TITLE_STRING_GAME_END };

// logo
const D3DXVECTOR2 LOGO_DEFAULT_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f,300.0f);
const D3DXVECTOR2 LOGO_DEST_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f,230.0f);


//=============================================================================
// constructor
//=============================================================================
SceneTitle::SceneTitle(void)
	:Scene(TYPE_TITLE)
	,bg_(nullptr)
	,logo_(nullptr)
	,push_(nullptr)
	,push_frame_(nullptr)
	,luminescence_(nullptr)
	,circle_(nullptr)
	,message_window_(nullptr)
	,option_(nullptr)
	,frame_count_(0)
	,current_select_(0)
	,decide_interval_(0)
	,mode_(MODE_PUSH)
{
	memset(select_, 0, sizeof(select_));
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
	GET_BGM->Play(BGM::BGM_ID_TITLE);

	bg_ = new TitleBg();
	bg_->Initialize();

	luminescence_ = new Titleluminescence();
	luminescence_->Initialize();

	circle_ = new TitleCircle();
	circle_->Initialize();

	logo_ = new TitleLogo();
	logo_->Initialize();

	push_ = new TitlePushStart();
	push_->Initialize();
	push_->__color(DEFAULT_COLOR);
	push_->__size(PUSH_START_SIZE);

	push_frame_ = new TitlePushStart();
	push_frame_->Initialize();
	push_frame_->__color(DEFAULT_COLOR);
	push_frame_->__size(PUSH_FRAME_SIZE);
	push_frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_000);
	
	for(int i = 0 ; i < SELECT_MAX ; i++){
		select_[i].frame_ = new TitleSelect();
		select_[i].select_ = new TitleSelect();
		select_[i].frame_->Initialize();
		select_[i].select_->Initialize();

		// texture
		select_[i].select_->__texture_id(SELECT_STRING_TEXTURE[i]);

		// frame size
		select_[i].frame_->__size(FRAME_SIZE);

		// position
		const D3DXVECTOR2 position = D3DXVECTOR2(SELECT_POSITION.x, SELECT_POSITION.y + (i * SELECT_OFFSET_Y));
		select_[i].frame_->__position(position);
		select_[i].select_->__position(position);
	}
	select_[current_select_].frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_001);

	// message_window
	message_window_ = new MessageWindow();
	message_window_->Initialize();
	message_window_->__dest_frame_count(DEST_FRAME_COUNT);
	message_window_->__title_texture_id_(Texture::TEXTURE_ID_TITLE_STRING_CONFIRM_END);

	// option
	option_ = new Option();
	option_->Initialize();

	//選択中のステージをチュートリアルに戻す
	System::__set_current_stage(1);

	frame_count_ = 0;
	current_select_ = 0;

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void SceneTitle::Uninitialize(void)
{
	SafeRelease(bg_);

	SafeRelease(logo_);

	SafeRelease(push_);

	SafeRelease(push_frame_);

	SafeRelease(luminescence_);

	SafeRelease(circle_);

	for(int i = 0 ; i < SELECT_MAX ; i++){
		SafeRelease(select_[i].frame_);
		SafeRelease(select_[i].select_);
	}

	SafeRelease(message_window_);

	SafeRelease(option_);

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
		// 背景発光
		_UpdateLuminescence();

		// 時間経過でロゴに戻る
		if(mode_ == MODE_PUSH || mode_ == MODE_SELECT)
		{
			frame_count_++;
			if(frame_count_ >= GO_LOGO_FRAME)
			{
				if(next_scene_factory_ == nullptr)
				{
					next_scene_factory_ = new LogoFactory();
				}
			}
		}

		// PUSH ENTER点滅
		if(mode_ == MODE_PUSH)
		{
			_UpdatePush();
		}
		if(mode_ == MODE_PUSH_INTERVAL)
		{
			decide_interval_--;
			if(decide_interval_ <= 0){
				mode_ = MODE_SELECT;
			}
		}
		// 選択肢処理
		else if(mode_ == MODE_SELECT && !message_window_->__is_show())
		{
			_UpdateSelect();
		}
		// メッセージウィンドウ
		else if(mode_ == MODE_MESSAGE && message_window_->__is_move() == false)
		{
			_UpdateMessage();
		}
		// オプション
		else if(mode_ == MODE_OPTION)
		{
			option_->Update();
			if(option_->__is_indication() == false){
				mode_ = MODE_SELECT;
				select_[current_select_].frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_001);
			}
		}

		message_window_->Update();
		logo_->Update();
	}

	// サークルの回転
	circle_->AddRotation(CIRCLE_ROTATION);
}

//=============================================================================
// draw
//=============================================================================
void SceneTitle::Draw(void)
{
	bg_->Draw();
	luminescence_->Draw();
	circle_->Draw();
	logo_->Draw();

	if(mode_ == MODE_PUSH || mode_ == MODE_PUSH_INTERVAL)
	{
		push_frame_->Draw();
		push_->Draw();
	}

	if(mode_ == MODE_SELECT || mode_ == MODE_MESSAGE)
	{
		for(int i = 0 ; i < SELECT_MAX ; i++){
			select_[i].frame_->Draw();
			select_[i].select_->Draw();
		}
	}
	option_->Draw();

	message_window_->Draw();
}

//=============================================================================
// create factory
//=============================================================================
SceneFactory* SceneTitle::CreateFactory(void)const
{
	return new TitleFactory();
}


//=============================================================================
// _UpdatePush
//=============================================================================
void SceneTitle::_UpdatePush(void)
{
	// アルファ取得
	f32 alpha = push_->__alpha();

	// アルファ値加算
	alpha += push_->__alpha_speed();

	if( alpha > PUSH_START_ALPHA_MAX )
	{
		alpha = PUSH_START_ALPHA_MAX;
		push_->InverseAlphaSpeed();
		push_frame_->InverseAlphaSpeed();
	}
	else if( alpha < PUSH_START_ALPHA_MIN )
	{
		alpha  = PUSH_START_ALPHA_MIN;
		push_->InverseAlphaSpeed();
		push_frame_->InverseAlphaSpeed();
	}

	// 設定
	push_->__alpha(alpha);
	push_->__color(D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha));
	push_frame_->__alpha(alpha);
	push_frame_->__color(D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha));

	// モード変更
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_DECIDE))
	{
		GET_SE->Play(SE::SE_ID_DECIDE);
		decide_interval_ = DESIDE_INTERVAL_COUNT;
		mode_ = MODE_PUSH_INTERVAL;

		// 初期値に戻しておく
		push_->ResetAlphaSpeed();
		push_->__alpha(DEFAULT_COLOR.a);
		push_->__color(DEFAULT_COLOR);

		push_frame_->ResetAlphaSpeed();
		push_frame_->__alpha(DEFAULT_COLOR.a);
		push_frame_->__color(DEFAULT_COLOR);

		// 決定枠テクスチャ
		push_frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_002);

		// logo
		logo_->__dest_position(LOGO_DEST_POSITION);
		logo_->StartMove();
	}
}

//=============================================================================
// _UpdateSelect
//=============================================================================
void SceneTitle::_UpdateSelect(void)
{
	// 現在の選択肢保存
	bool input = false;
	bool decide = false;
	const s16 oldSelect = current_select_;

	// 選択肢移動の入力
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_UP))
	{
		GET_SE->Play(SE::SE_ID_CURSOR);
		current_select_--;
		input = true;
		if(current_select_ < 0) current_select_ = SELECT_MAX - 1;
	}
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_DOWN))
	{
		GET_SE->Play(SE::SE_ID_CURSOR);
		current_select_++;
		input = true;
		if(current_select_ >= SELECT_MAX) current_select_ = 0;
	}

	// キャンセル
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_CANCEL))
	{
		// 選択肢を戻しておく
		GET_SE->Play(SE::SE_ID_CANCEL);
		mode_ = MODE_PUSH;
		current_select_ = SELECT_START;
		for(int i = 0 ; i < SELECT_MAX ; i++){
			select_[i].frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_000);
		}
		select_[current_select_].frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_001);

		// push
		push_frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_000);

		// logo
		logo_->__dest_position(LOGO_DEFAULT_POSITION);
		logo_->StartMove();
	}

	// 決定
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_DECIDE) && !message_window_->__is_move())
	{
		GET_SE->Play(SE::SE_ID_DECIDE);
		decide = true;

		// 選択肢ごとに処理
		switch((SELECT_TYPE)current_select_)
		{
		case SELECT_START:
			if(next_scene_factory_ == nullptr){
				next_scene_factory_ = new GameFactory();
			}
			break;

		case SELECT_OPTION:
			mode_ = MODE_OPTION;
			option_->__is_indication(true);
			break;

		case SELECT_END:
			if(message_window_->__is_move() == false){
				mode_ = MODE_MESSAGE;
				message_window_->Show();
			}
			break;
		}
	}

	// 入力があった
	if(input)
	{
		frame_count_ = 0;
		select_[oldSelect].frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_000);
		select_[current_select_].frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_001);
	} // select
	
	if(decide)
	{
		select_[current_select_].frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_002);
	}
}

//=============================================================================
// _UpdateMessage
//=============================================================================
void SceneTitle::_UpdateMessage(void)
{
	if(is_stop_) return;

	message_window_->__title_texture_id_(Texture::TEXTURE_ID_TITLE_STRING_CONFIRM_END);

	// 自動遷移止める
	frame_count_ = 0;

	// メッセージの選択処理
	if(message_window_->__is_show()){

		if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_LEFT))
		{
			message_window_->SelectDown();
		}
		if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_RIGHT))
		{
			message_window_->SelectUp();
		}

		if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_DECIDE))
		{
			GET_SE->Play(SE::SE_ID_DECIDE);
			const s32 current_select = message_window_->__is_select();
			message_window_->__select_frame_texture_id_(current_select, Texture::TEXTURE_ID_TITLE_SELECT_FRAME_002);

			if(current_select == MessageWindow::MESSAGE_NO)
			{
				message_window_->Close();
				mode_ = MODE_SELECT;
				select_[current_select_].frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_001);
			}
			if((current_select == MessageWindow::MESSAGE_YES))
			{
				is_stop_ = true;
			}
		}
	} // is_show
}

//=============================================================================
// _UpdateLuminescence
//=============================================================================
void SceneTitle::_UpdateLuminescence(void)
{
	// アルファ取得
	f32 alpha = luminescence_->__alpha();

	// アルファ値加算
	alpha += luminescence_->__alpha_speed();

	if( alpha > LUMINESCENCE_ALPHA_MAX )
	{
		alpha = LUMINESCENCE_ALPHA_MAX;
		luminescence_->InverseAlphaSpeed();
	}
	else if( alpha < LUMINESCENCE_ALPHA_MIN)
	{
		alpha  = LUMINESCENCE_ALPHA_MIN;
		luminescence_->InverseAlphaSpeed();
	}

	// 設定
	luminescence_->__alpha(alpha);
	luminescence_->__color(D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha));
}



//---------------------------------- EOF --------------------------------------
