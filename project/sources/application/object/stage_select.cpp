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
#include "stage_select/select_bg.h"
#include "stage_region.h"
#include "render/sprite.h"
#include "system/system.h"
#include "scene/game/scene_game.h"
#include "stage_select/select_arrow.h"
#include "message_window.h"

//*****************************************************************************
// constant definition
//*****************************************************************************


const u32 DEST_FRAME_COUNT = 20;				// ウィンドウ開閉の時間
const f32 REGIONS_INTERVAL = 600.0f;			// レギオン同士の間隔 x方向


//=============================================================================
// constructor
//=============================================================================
StageSelect::StageSelect(void)
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
	if(!SafeInitialize(select_bg_))
	{
		return false;
	}

	//ブルーニャス

	//セレクト矢印
	select_arrow_ = new SelectArrow();
	if(!SafeInitialize(select_arrow_))
	{
		return false;
	}


	//セレクト枠xステージ数
	for(u32 i=0;i<STAGE_ID_MAX;i++)
	{
		//まとまりを作る
		regions_[i] = new StageRegion();
		if(!SafeInitialize(regions_[i]))
		{
			return false;
		}
		//まとまりにステージ名を与える
		regions_[i]->__set_stage_id((STAGE_ID)i);
		regions_[i]->__set_region_distpos(D3DXVECTOR2(i*REGIONS_INTERVAL,0.0f));
	}

	//スコアタイム割り当て（暫定）
	regions_[0]->__set_time(0);
	regions_[1]->__set_time(234);
	regions_[2]->__set_time(181);

	// message_window
	message_window_ = new MessageWindow();
	message_window_->Initialize();
	message_window_->__dest_frame_count(DEST_FRAME_COUNT);

	massage_flag_ = false;

	update_type_ = UPDATE_TYPE_SELECT;

	//今のステージ
	current_stage_ = 0;

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void StageSelect::Uninitialize(void)
{
	SafeRelease(select_bg_);
	SafeRelease(select_arrow_);	

	for(u32 i=0;i<STAGE_ID_MAX;i++)
	{
		SafeRelease(regions_[i]);
	}
	SafeRelease(message_window_);

}

//=============================================================================
// update
//=============================================================================
void StageSelect::Update(void)
{
	switch(update_type_)
	{
	case UPDATE_TYPE_SELECT:
		SelectUpdate();
		break;
	case UPDATE_TYPE_MASSAGE:
		MassageUpdate();
		break;
	case UPDATE_TYPE_YORN:

		break;
	}
	message_window_->Update();
}

//=============================================================================
// draw
//=============================================================================
void StageSelect::Draw(void)
{
	select_bg_->Draw();

	for(u32 i=0;i<STAGE_ID_MAX;i++)
	{
		regions_[i]->Draw();
	}

	select_arrow_->Draw();

	message_window_->Draw();
}

//=============================================================================
// ステージを選んでるときの更新
//=============================================================================
void StageSelect::SelectUpdate()
{
	//選択中のステージが右端じゃないとき
	if(current_stage_ !=STAGE_ID_MAX-1)
	{
		if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_RIGHT))
		{
			for(u32 i=0;i<STAGE_ID_MAX;i++)
			{
				regions_[i]->__set_region_distpos(D3DXVECTOR2(-REGIONS_INTERVAL,0.0f));
			}
			current_stage_++;
		}
	}
	//選択中のステージが左端じゃないとき
	if(current_stage_!=0)
	{
		if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_LEFT))
		{
			for(u32 i=0;i<STAGE_ID_MAX;i++)
			{
				regions_[i]->__set_region_distpos(D3DXVECTOR2(REGIONS_INTERVAL,0.0f));
			}
			current_stage_--;
		}
	}

	//決定を押されたとき選択中のステージを伝える
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_RETURN))
	{
		if(message_window_->__is_move() == false)
		{
			message_window_->Show();
		}
		update_type_ = UPDATE_TYPE_YORN;

	}
	//矢印に選択中のステージを伝えて更新
	select_arrow_->__set_stage_id((STAGE_ID)current_stage_);
	select_arrow_ ->Update();

	//まとまりに更新をかける
	for(u32 i=0;i<STAGE_ID_MAX;i++)
	{
		regions_[i]->Update();
	}
	//キャンセル押されたときメッセージ表示
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_CANCEL))
	{
		if(message_window_->__is_move() == false)
		{
			message_window_->Show();
		}
		update_type_ = UPDATE_TYPE_MASSAGE;
	}

}
//=============================================================================
// メッセージウィンドウが出てるときの更新
//=============================================================================
void StageSelect::MassageUpdate()
{
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
	if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_RETURN))
	{
		//イエスの時
		if(message_window_->__is_select() == 0)
		{
			// タイトルに戻る
			SceneGame::__next_stage(STAGE_ID_END);
		}
		//ノーの時
		if(message_window_->__is_select() == 1)
		{
			//ウィンドウを閉じる
			if(message_window_->__is_move() == false)
			{
				message_window_->Close();
			}
			update_type_ = UPDATE_TYPE_SELECT;
		}
	}

	//キャンセル押されたときメッセージ表示
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_CANCEL))
	{
		if(message_window_->__is_move() == false)
		{
			message_window_->Close();
		}
		update_type_ = UPDATE_TYPE_SELECT;
	}
}

//=============================================================================
// ホントにこのステージで遊ぶか聞いてるときの更新
//=============================================================================
void StageSelect::YorNUpdate()
{
	SceneGame::__next_stage((STAGE_ID)current_stage_);

}



//---------------------------------- EOF --------------------------------------
