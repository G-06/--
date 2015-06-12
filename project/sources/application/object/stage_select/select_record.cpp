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

const u32 NUMBER_SIZE_X = 50;	//êîéö1Ç¬ÇÃâ°ïù
const f32 DEFAULT_POSX = 400;	//ç∂í[ÇÃêîéöÇÃX
const f32 DEFAULT_POSY = 500;	//ç∂í[ÇÃêîéöÇÃY


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
		number_[i] ->__Set_position(D3DXVECTOR2((f32)NUMBER_SIZE_X*i+DEFAULT_POSX,DEFAULT_POSY));
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

	//ïbÇäÑÇËèoÇ∑
	sec = workA%60;
	//ïbÇà¯Ç¢Çƒï™ÇÃÇ›Ç…Ç∑ÇÈ
	workA-=sec;
	//Ç”ÇÒÇäÑÇËèoÇ∑
	min=workA/60;


	workA = min;
	//ï™Å@ÇPÇOÇÃà 
	workB = (f32)(workA%10);
	number_[1]->__Set_index((u32)workB);
	workA -= (u32)workB;
	workA /= 10;

	//ï™Å@ÇPÇÃà 
	workB = (f32)(workA%10);
	number_[0]->__Set_index((u32)workB);
	workA -= (u32)workB;
	workA /= 10;

	workA = sec;
	//ïbÅ@ÇPÇOÇÃà 
	workB = (f32)(workA%10);
	number_[3]->__Set_index((u32)workB);
	workA -= (u32)workB;
	workA /= 10;

	//ïbÅ@ÇPÇÃà 
	workB = (f32)(workA%10);
	number_[2]->__Set_index((u32)workB);
	workA -= (u32)workB;
	workA /= 10;

}

//---------------------------------- EOF --------------------------------------
