//*****************************************************************************
//
// stage select bg
//
// Author		: taichi kitazawa
//
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "select_record.h"
#include "select_number.h"
#include "render/sprite.h"
#include "system/system.h"
#include "select_record_back.h"

static const D3DXVECTOR2 DEFAULT_POS_NUM(680.f,500.f);		// デフォルトポジション 数字の一番左端の位置
static const D3DXVECTOR2 DEFAULT_POS_BACK(800.f,500.f);		// デフォルトポジション 数字の一番左端の位置
 

//=============================================================================
// constructor
//=============================================================================
SelectRecord::SelectRecord(void)
{

}

//=============================================================================
// destructor
//=============================================================================
SelectRecord::~SelectRecord(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool SelectRecord::Initialize(void)
{
	//数字
	for(int i=0;i<TEXTURE_MAX;i++)
	{
		number_[i] = new Number();
		number_[i] -> Initialize();
		number_[i] ->__Set_position(D3DXVECTOR2((f32)35*i+DEFAULT_POS_NUM.x,DEFAULT_POS_NUM.y));
	}
	//背景
	record_back_ = new RecordBack();
	record_back_->Initialize();

	//位置
	offset_position_ = D3DXVECTOR2(0,0);
	time_ =0;
	__set_time(time_);

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void SelectRecord::Uninitialize(void)
{
	for(int i=0;i<TEXTURE_MAX;i++)
	{
		SafeRelease(number_[i]);
	}
	SafeRelease(record_back_);
}

//=============================================================================
// update
//=============================================================================
void SelectRecord::Update(void)
{
	record_back_ ->__offset_position(offset_position_);
	record_back_ ->Update();
	for(int i=0;i<TEXTURE_MAX;i++)
	{
		number_[i]->__offset_position(offset_position_);
		number_[i]->Update();
	}
}

//=============================================================================
// draw
//=============================================================================
void SelectRecord::Draw(void)
{
	record_back_->Draw();
	for(int i=0;i<TEXTURE_MAX;i++)
	{
		number_[i]->Draw();
	}
}

void SelectRecord::__set_time(u32 time)
{
	time_=time;
	//
	u32 workA=0;
	f32 workB=0;

	u32 min=0;
	u32 sec=0;
	u32 mlisec=0;

	workA = time_;

	//ミリ秒をだす
	mlisec=workA%60;
	workA-=mlisec;
	workA /= 60;
	//秒を割り出す
	sec = workA%60;
	workA -= sec;
	workA/=60;
	//ふんを割り出す
	min=workA;

	workA = min;
	//分　１０の位
	workB = (f32)(workA%10);
	number_[1]->__Set_index((u32)workB);
	workA -= (u32)workB;
	workA /= 10;

	//分　１の位
	workB = (f32)(workA%10);
	number_[0]->__Set_index((u32)workB);
	workA -= (u32)workB;
	workA /= 10;

	//ころん
	number_[2]->__Set_index(11);

	workA = sec;
	//秒　１０の位
	workB = (f32)(workA%10);
	number_[4]->__Set_index((u32)workB);
	workA -= (u32)workB;
	workA /= 10;

	//秒　１の位
	workB = (f32)(workA%10);
	number_[3]->__Set_index((u32)workB);
	workA -= (u32)workB;
	workA /= 10;

	//dotto
	number_[5]->__Set_index(12);

	workA = mlisec;
	//秒　１０の位
	workB = (f32)(workA%10);
	number_[7]->__Set_index((u32)workB);
	workA -= (u32)workB;
	workA /= 10;

	//秒　１の位
	workB = (f32)(workA%10);
	number_[6]->__Set_index((u32)workB);
	workA -= (u32)workB;
	workA /= 10;

}

//=============================================================================
// set pos
//=============================================================================
void SelectRecord::__set_position(D3DXVECTOR2 pos)
{
	record_back_ ->__Set_position(pos);
	pos.x = pos.x - (DEFAULT_POS_BACK.x-DEFAULT_POS_NUM.x);

	for(int i=0;i<TEXTURE_MAX;i++)
	{
		number_[i]->__Set_position(D3DXVECTOR2((f32)35*i+pos.x,pos.y));
	}
}

//---------------------------------- EOF --------------------------------------
