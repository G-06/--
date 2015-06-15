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
	//
	for(int i=0;i<4;i++)
	{
		number_[i] = new Number();
		number_[i] -> Initialize();
		number_[i] ->__Set_position(D3DXVECTOR2((f32)50*i+540,600));
	}
	record_back_ = new RecordBack();
	record_back_->Initialize();

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
	for(int i=0;i<4;i++)
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
	for(int i=0;i<4;i++)
	{
		number_[i] ->__Set_position(D3DXVECTOR2(50*i+540 + offset_position_.x,600));
		number_[i]->Update();
	}
}

//=============================================================================
// draw
//=============================================================================
void SelectRecord::Draw(void)
{
	record_back_->Draw();
	for(int i=0;i<4;i++)
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

	workA = time_;

	//秒を割り出す
	sec = workA%60;
	//秒を引いて分のみにする
	workA-=sec;
	//ふんを割り出す
	min=workA/60;

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

	workA = sec;
	//秒　１０の位
	workB = (f32)(workA%10);
	number_[3]->__Set_index((u32)workB);
	workA -= (u32)workB;
	workA /= 10;

	//秒　１の位
	workB = (f32)(workA%10);
	number_[2]->__Set_index((u32)workB);
	workA -= (u32)workB;
	workA /= 10;
}

//---------------------------------- EOF --------------------------------------
