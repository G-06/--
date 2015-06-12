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
		number_[i] ->__Set_position(D3DXVECTOR2((f32)50*i+400,500));
	}
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
}

//=============================================================================
// update
//=============================================================================
void SelectRecord::Update(void)
{


	for(int i=0;i<4;i++)
	{
		number_[i] ->__Set_position(D3DXVECTOR2(50*i+400 + offset_position_.x,500));
		number_[i]->Update();
	}

}

//=============================================================================
// draw
//=============================================================================
void SelectRecord::Draw(void)
{
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

	//•b‚ðŠ„‚èo‚·
	sec = workA%60;
	//•b‚ðˆø‚¢‚Ä•ª‚Ì‚Ý‚É‚·‚é
	workA-=sec;
	//‚Ó‚ñ‚ðŠ„‚èo‚·
	min=workA/60;


	workA = min;
	//•ª@‚P‚O‚ÌˆÊ
	workB = (f32)(workA%10);
	number_[1]->__Set_index((u32)workB);
	workA -= (u32)workB;
	workA /= 10;

	//•ª@‚P‚ÌˆÊ
	workB = (f32)(workA%10);
	number_[0]->__Set_index((u32)workB);
	workA -= (u32)workB;
	workA /= 10;

	workA = sec;
	//•b@‚P‚O‚ÌˆÊ
	workB = (f32)(workA%10);
	number_[3]->__Set_index((u32)workB);
	workA -= (u32)workB;
	workA /= 10;

	//•b@‚P‚ÌˆÊ
	workB = (f32)(workA%10);
	number_[2]->__Set_index((u32)workB);
	workA -= (u32)workB;
	workA /= 10;

}

//---------------------------------- EOF --------------------------------------
