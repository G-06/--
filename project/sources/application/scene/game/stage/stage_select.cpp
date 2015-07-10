//*****************************************************************************
//
// stage select
//
// Author		: kitazawa taichi
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "stage_select.h"
#include "stage_factory.h"
#include "stage_manager.h"
#include "application/object/stage_select/select_bg.h"
#include "application/object/stage_region.h"
#include "render/sprite.h"
#include "system/system.h"
#include "scene/game/scene_game.h"
#include "application/object/stage_select/select_arrow.h"
#include "application/object/message_window.h"
#include "scene/factory/scene_factory.h"
#include "application/object/object_player.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const u32 DEST_FRAME_COUNT = 20;						// ウィンドウ開閉の時間
const f32 REGION_INTERVAL = (850.0f*0.87f)*1.3f;		// レギオンの間隔
const f32 REGION_MOVE = 960.f;							// レギオンの間隔

static const u32 RIGHT = 1;
static const u32 LEFT = 2;

//=============================================================================
// constructor
//=============================================================================
StageSelect::StageSelect(void)
		:Stage(TYPE_SELECT)
{
}

//=============================================================================
// destructor
//=============================================================================
StageSelect::~StageSelect(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool StageSelect::Initialize(void)
{
	//背景
	select_bg_ = new SelectBg();
	select_bg_->Initialize();

	//ブルーニャス
	nas_ = new ObjectPlayer();
	nas_ -> Initialize();
	nas_ -> __position(D3DXVECTOR2(260.f,510.f));
	nas_ -> StartAnimation(ObjectPlayer::ANIMATION_TYPE_WAIT);
	nas_->__is_flip(false);
	const f32 scale = 1.2f;
	nas_->SetSize(D3DXVECTOR2(255.0f * scale,255.0f * scale));
	//矢印
	select_arrow_ = new SelectArrow();
	select_arrow_ ->Initialize();

	//レコードファイル読み込み
//	System::FileLoad("data/stage/record.bin");
	////レコードファイル出力
//	System::FileSave("data/stage/record.bin");

	//今のステージ
	current_stage_ = System::__get_current_stage();

	////セレクト枠xステージ数
	for(u32 i=0;i<TYPE_MAX-1;i++)
	{
		regions_[i].region_ = new StageRegion();
		regions_[i].region_->Initialize();
		regions_[i].position_ = D3DXVECTOR2((i*REGION_INTERVAL)-((current_stage_-1)*REGION_MOVE), 50.0f);
		regions_[i].region_->__set_position(regions_[i].position_);
		regions_[i].type_ = ((TYPE)(i+1));
		regions_[i].region_->__set_stage_id(regions_[i].type_);
		regions_[i].region_->__set_time(System::RecordLoad(i));
	}

	// message_window
	message_window_ = new MessageWindow();
	message_window_->Initialize();
	message_window_->__dest_frame_count(DEST_FRAME_COUNT);
	message_window_->__title_texture_id_(Texture::TEXTURE_ID_SELECT_STRING_RETURN_TITLE);
	massage_flag_ = false;

	update_type_ = UPDATE_TYPE_SELECT;

	flag_ = 0;

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void StageSelect::Uninitialize(void)
{
	SafeRelease(select_bg_);
	SafeRelease(select_arrow_);	
	SafeRelease(message_window_);
	SafeRelease(nas_);
	for(u32 i=0;i<TYPE_MAX-1;i++)
	{
		SafeRelease(regions_[i].region_);
	}
	SafeDelete(next_stage_factory_);
}

//=============================================================================
// update
//=============================================================================
void StageSelect::Update(void)
{

	if(next_stage_factory_ == nullptr)
	{
		switch(update_type_)
		{
		case UPDATE_TYPE_SELECT:		//遊びたいステージを選ぶ
			SelectUpdate();
			break;
		case UPDATE_TYPE_MASSAGE:		//タイトルに戻る？
			MassageUpdate();
			break;
		case UPDATE_TYPE_YORN:			//このステージで遊ぶ?
			YorNUpdate();
			break;
		}

		//ニャス更新
		if(regions_[0].region_->__get_move_falg() == false)
		{
			nas_->__is_flip(false);
			nas_->StartAnimation(ObjectPlayer::ANIMATION_TYPE_WAIT);
		}
		else if(regions_[0].region_->__get_move_falg() == true)
		{
			nas_->StartAnimation(ObjectPlayer::ANIMATION_TYPE_RUN);
		}
		nas_->Update();
	}
		message_window_->Update();
}


//=============================================================================
// draw
//=============================================================================
void StageSelect::Draw(void)
{
	select_bg_->Draw();

	for(u32 i=0;i<TYPE_MAX-1;i++)
	{
		regions_[i].region_->Draw();
	}

	if(regions_[1].region_->__get_move_falg() == false)
		select_arrow_->Draw();

	message_window_->Draw();
	nas_->Draw();
}

//=============================================================================
// ステージを選んでるときの更新
//=============================================================================
void StageSelect::SelectUpdate()
{
	if(regions_[0].region_->__get_move_falg() == false)	//レギオンが動いてないとき
	{
		//必要以上に右に行かない
		if(current_stage_ !=TYPE_MAX-1)
		{
			if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_VIRTUAL_RIGHT))
			{
				for(u32 i=0;i<TYPE_MAX-1;i++)
				{
					regions_[i].region_->__set_region_distpos(D3DXVECTOR2(-REGION_MOVE,0.0f));
					flag_=RIGHT;
				}
				current_stage_++;
				nas_->__is_flip(false);
			}
		}

		//必要以上に左に行かない
		if(current_stage_!=TYPE_TUTORIAL)
		{
			if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_VIRTUAL_LEFT))
			{
				for(u32 i=0;i<TYPE_MAX-1;i++)
				{
					regions_[i].region_->__set_region_distpos(D3DXVECTOR2(REGION_MOVE,0.0f));
					flag_=LEFT;
				}
				current_stage_--;
				nas_->__is_flip(true);
			}
		}

		//決定押されたとき
		if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_DECIDE))
		{
			if(message_window_->__is_move() == false)
			{
				message_window_->Show();
				update_type_ = UPDATE_TYPE_YORN;
			}
		}
		//キャンセル押されたときメッセージ表示
		if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_CANCEL))
		{
			if(message_window_->__is_move() == false)
			{
				message_window_->Show();
				update_type_ = UPDATE_TYPE_MASSAGE;
			}
		}
	}
	else if(regions_[0].region_->__get_move_falg() == true)	//レギオンが動いているとき
	{
		if(flag_==RIGHT)
		{
			select_bg_->__set_move_uv(-0.006f);
		}
		else if(flag_==LEFT)
		{
			select_bg_->__set_move_uv(0.006f);
		}
	}
	//背景更新
	select_bg_->Update();

	//矢印更新
	select_arrow_->__set_stage_id((Stage::TYPE)current_stage_);
	select_arrow_ ->Update();

	//まとまりに更新をかける
	for(u32 i=0;i<TYPE_MAX-1;i++)
	{
		regions_[i].region_->Update();
	}

	if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_R))
	{
		//レコード初期化
		System::RecordSave(0,65535);
		System::RecordSave(1,65535);
		System::RecordSave(2,65535);
		System::RecordSave(3,65535);
		System::RecordSave(4,65535);
		System::RecordSave(5,65535);
		System::RecordSave(6,65535);
		System::RecordSave(7,65535);
		System::RecordSave(8,65535);
		System::RecordSave(9,65535);
		System::RecordSave(10,65535);

		if(next_stage_factory_ == nullptr)
		{
			next_stage_factory_ = new SelectFactory();
		}
	}
}

//=============================================================================
// メッセージウィンドウが出てるときの更新
//=============================================================================
void StageSelect::MassageUpdate()
{
	message_window_->__title_texture_id_(Texture::TEXTURE_ID_SELECT_STRING_RETURN_TITLE);

	//十字キー入力時
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_LEFT))
	{
		message_window_->SelectDown();
	}
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_RIGHT))
	{
		message_window_->SelectUp();
	}
	//決定キー押されたとき
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_DECIDE))
	{
		// 枠を決定色に変更
		message_window_->__select_frame_texture_id_(message_window_->__is_select(), Texture::TEXTURE_ID_TITLE_SELECT_FRAME_002);

		//イエスの時
		if(message_window_->__is_select() == 0)
		{
			// タイトルに戻る
			if(next_scene_factory_ == nullptr)
			{
				next_scene_factory_ = new TitleFactory();
			}
		}
		//ノーの時
		if(message_window_->__is_select() == 1)
		{
			//ウィンドウを閉じる
			if(message_window_->__is_move() == false)
			{
				message_window_->Close();
				update_type_ = UPDATE_TYPE_SELECT;
			}
		}
	}

	//キャンセル押されたときメッセージけし
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_CANCEL))
	{
		if(message_window_->__is_move() == false)
		{
			message_window_->Close();
			update_type_ = UPDATE_TYPE_SELECT;
		}
	}
}

//=============================================================================
// ホントにこのステージで遊ぶか聞いてるときの更新
//=============================================================================
void StageSelect::YorNUpdate()
{
	message_window_->__title_texture_id_(Texture::TEXTURE_ID_SELECT_STRING_STAGE_OK);

	//十字キー入力時
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_LEFT))
	{
		message_window_->SelectDown();
	}
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_RIGHT))
	{
		message_window_->SelectUp();
	}

	//決定キー押されたとき
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_DECIDE))
	{
		//イエスの時
		if(message_window_->__is_select() == 0)
		{
			if(next_stage_factory_ == nullptr)
			{
				// 枠を決定色に変更
				message_window_->__select_frame_texture_id_(message_window_->__is_select(), Texture::TEXTURE_ID_TITLE_SELECT_FRAME_002);

				//ナウステージおしえます
				System::__set_current_stage(current_stage_);

				//ゲームに移る
				switch(current_stage_)
				{
				case TYPE_TUTORIAL:		//チュートリアル行くぜ
				default:
						next_stage_factory_ = new TutorialFactory();
					break;
				case TYPE_STAGE1:
					next_stage_factory_ = new StageOneFactory();
					break;
				case TYPE_STAGE2:
					next_stage_factory_ = new StageTwoFactory();
					break;
				case TYPE_STAGE3:
					next_stage_factory_ = new StageThreeFactory();
					break;
				case TYPE_STAGE4:
					next_stage_factory_ = new StageFourFactory();
					break;
				case TYPE_STAGE5:
					next_stage_factory_ = new StageFiveFactory();
					break;
				case TYPE_STAGE6:
					next_stage_factory_ = new StageSixFactory();
					break;
				case TYPE_STAGE7:
					next_stage_factory_ = new StageSevenFactory();
					break;
				case TYPE_STAGE8:
					next_stage_factory_ = new StageEightFactory();
					break;
				case TYPE_STAGE9:
					next_stage_factory_ = new StageNineFactory();
					break;
				case TYPE_STAGE10:
					next_stage_factory_ = new StageTenFactory();
					break;
				}
			}
		}
		//メッセージを閉じる
		if(message_window_->__is_select() == 1)
		{
			if(message_window_->__is_move() == false)
			{
				// 枠を決定色に変更
				message_window_->__select_frame_texture_id_(message_window_->__is_select(), Texture::TEXTURE_ID_TITLE_SELECT_FRAME_002);

				message_window_->Close();
				update_type_ = UPDATE_TYPE_SELECT;
			}
		}
	}

	//キャンセル押されたときメッセージけし
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_CANCEL))
	{
		if(message_window_->__is_move() == false)
		{
			message_window_->Close();
			update_type_ = UPDATE_TYPE_SELECT;
		}
	}
}

//=============================================================================
// create factory
//=============================================================================
StageFactory* StageSelect::CreateFactory(void)const
{
	return new SelectFactory();
}

//---------------------------------- EOF --------------------------------------
