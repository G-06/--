//*****************************************************************************
//
// gimmick チュートリアルてきすと
//
// Author		: kitazawa taichi
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "gimmick_massage.h"
#include "render/text_box.h"
#include "system/directx9/font/font_texture.h"
#include "application/object/message_window.h"
#include "application/object/tutorial_back.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const u32 DEST_FRAME_COUNT = 15;						// ウィンドウ開閉の時間
const D3DXVECTOR2 DEFAULT_POS_BACK (DEFAULT_SCREEN_WIDTH * 0.5f, DEFAULT_SCREEN_HEIGHT * 0.27f);		//テキスト背景の位置
const D3DXVECTOR2 DEFAULT_TXT_BACK (DEFAULT_SCREEN_WIDTH * 0.24f, DEFAULT_SCREEN_HEIGHT * 0.16f);		//文字の開始位置
const D3DXCOLOR TEXT_COLOR = D3DXCOLOR(1.0f, 1.0f, 0.3f, 1.0f);

//=============================================================================
// constructor
//=============================================================================
GimmickMassage::GimmickMassage(void)
	:Gimmick(TYPE_MASSAGE)
{
	size_ = D3DXVECTOR2(2300.0f,2600.0f);
}

//=============================================================================
// destructor
//=============================================================================
GimmickMassage::~GimmickMassage(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool GimmickMassage::Initialize(void)
{
	txtbox_ = new TextBox(FontTexture::TYPE_MEIRYO,50);
	txtbox_->Initialize();
	txtbox_->__show_speed(2);

	txtbox_->__position(DEFAULT_TXT_BACK);

	switch(type_)
	{
	case MASSAGE_TYPE_STAFF_TITLE:
//			txtbox_->Print("ブルーニャス", TEXT_COLOR);
			txtbox_->Print("          BlueNyas\n\n", TEXT_COLOR);
			txtbox_->Print("     チーム ・ コネコバコ       ", TEXT_COLOR);
		break;
	case MASSAGE_TYPE_STAFF_MAKER:
			txtbox_->Print("\n     ☆つくった ひとたち☆", TEXT_COLOR);
		break;
	case MASSAGE_TYPE_STAFF_LEADER:
//			txtbox_->Print("リーダー\n  ますだ  まさと", TEXT_COLOR);
			txtbox_->Print("          リーダー\n", TEXT_COLOR);
			txtbox_->Print("       ますだ  まさと", TEXT_COLOR);
		break;
	case MASSAGE_TYPE_STAFF_DESIGNER:
//			txtbox_->Print("デザイナー\n  はまだ  みさ", TEXT_COLOR);
			txtbox_->Print("         デザイナー\n", TEXT_COLOR);
			txtbox_->Print("        はまだ  みさ", TEXT_COLOR);
		break;
	case MASSAGE_TYPE_STAFF_PLANER_1:
//			txtbox_->Print("プランナー\n  はやしだ  けいた", TEXT_COLOR);
			txtbox_->Print("         プランナー\n", TEXT_COLOR);
			txtbox_->Print("      はやしだ  けいた", TEXT_COLOR);
		break;
	case MASSAGE_TYPE_STAFF_PLANER_2:
//			txtbox_->Print("プランナー\n  ますこ  きょうすけ", TEXT_COLOR);
			txtbox_->Print("         プランナー\n", TEXT_COLOR);
			txtbox_->Print("      ますこ  きょうすけ", TEXT_COLOR);
		break;
	case MASSAGE_TYPE_STAFF_PROGRAMMER_1:
//			txtbox_->Print("メインプログラマー\n  かぶともり  けんじ", TEXT_COLOR);
			txtbox_->Print("      メインプログラマー\n", TEXT_COLOR);
			txtbox_->Print("      かぶともり  けんじ", TEXT_COLOR);
		break;
	case MASSAGE_TYPE_STAFF_PROGRAMMER_2:
//			txtbox_->Print("プログラマー\n  あらい  りょうたろう", TEXT_COLOR);
			txtbox_->Print("        プログラマー\n", TEXT_COLOR);
			txtbox_->Print("      あらい  りょうたろう", TEXT_COLOR);
		break;
	case MASSAGE_TYPE_STAFF_PROGRAMMER_3:
//			txtbox_->Print("プログラマー\n  きたざわ  たいち", TEXT_COLOR);
			txtbox_->Print("        プログラマー\n", TEXT_COLOR);
			txtbox_->Print("      きたざわ  たいち", TEXT_COLOR);
		break;
	case MASSAGE_TYPE_STAFF_PROGRAMMER_4:
//			txtbox_->Print("プログラマー\n  さいとう  はるき", TEXT_COLOR);
			txtbox_->Print("        プログラマー\n", TEXT_COLOR);
			txtbox_->Print("       さいとう  はるき", TEXT_COLOR);
		break;
	case MASSAGE_TYPE_STAFF_SPECIAL_1:
//			txtbox_->Print("サウンド素材\n  ポケットサウンド\n  くらげ工匠       効果音ラボ\n", TEXT_COLOR);
			txtbox_->Print("        サウンドそざい\n", TEXT_COLOR);
			txtbox_->Print("  ポケットサウンド\n  くらげ工匠     効果音ラボ\n", TEXT_COLOR);
		break;
	case MASSAGE_TYPE_STAFF_SPECIAL_2:
//			txtbox_->Print("スペシャルサンクス\n  やました  やすあき", TEXT_COLOR);
			txtbox_->Print("     スペシャルサンクス\n", TEXT_COLOR);
			txtbox_->Print("     やました  やすあき", TEXT_COLOR);
		break;

	default:
		txtbox_->Print("表示する文字がないニャス", TEXT_COLOR);
	break;
	}

	wait_ = 0;

	// message_window
	back_ = new TutorialBack();
	back_->Initialize();
	back_->__dest_frame_count(DEST_FRAME_COUNT);
	back_->__window_position(DEFAULT_POS_BACK);
	back_flag_ = false;

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void GimmickMassage::Uninitialize(void)
{
	SafeRelease(txtbox_);
	SafeRelease(back_);

}

//=============================================================================
// update
//=============================================================================
void GimmickMassage::Update(void)
{
	if(data_._is_hit == true)
	{
		if(back_flag_ == false)
		{
			back_->Show();
			back_flag_ = true;
		}
		if(wait_== DEST_FRAME_COUNT)
		{
			txtbox_->Restart();
		}
		wait_++;
	}
	else if(data_._is_hit == false)
	{
		if(back_flag_ == true)
		{
			back_->Close();
			wait_ = 0;
			back_flag_ = false;
		}
	}

	back_->Update();
	data_._is_hit=false;
}


//=============================================================================
// draw
//=============================================================================
void GimmickMassage::Draw(void)
{
	back_->Draw();
	if(wait_ > DEST_FRAME_COUNT)
	{
		txtbox_->Draw();
	}
}

//=============================================================================
// get pointer
//=============================================================================
void* GimmickMassage::GetPointer(void)
{
	return &data_;
}

//---------------------------------- EOF --------------------------------------

/*
ブルーニャス

☆つくった　ひとたち☆

リーダー
　ますだ　まさと

デザイナー
　はまだ　みさ

プランナー
　はやしだ　けいた
　ますこ　きょうすけ

メインプログラマー
　かぶともり　けんじ

プログラマー
　あらい　りょうたろう
　きたざわ　たいち
　さいとう　はるき

スペシャルサンクス
　やました　やすあき
　
　魔王魂

　
お　わ　り

　^　　^
( ◎ω◎)

*/
