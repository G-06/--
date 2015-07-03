//*****************************************************************************
//
// logo bg
//
// Author		: taichi kitazawa
//				: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "object_record.h"
#include "render/sprite.h"
#include "system/system.h"
#include "stage_select/select_record.h"
#include "stage_select/select_number.h"

static const D3DXVECTOR2 DEFAULT_POS_NUM(680.f,500.f);		// ÉfÉtÉHÉãÉgÉ|ÉWÉVÉáÉì êîéöÇÃàÍî‘ç∂í[ÇÃà íu


//=============================================================================
// constructor
//=============================================================================
ObjectRecord::ObjectRecord(void)
{
}

//=============================================================================
// destructor
//=============================================================================
ObjectRecord::~ObjectRecord(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool ObjectRecord::Initialize(void)
{
	//êîéö
	for(int i=0;i<TEXTURE_MAX;i++)
	{
		number_[i] = new Number();
		number_[i] -> Initialize();
		number_[i] ->__Set_position(D3DXVECTOR2((f32)35*i+0,0));
	}
	//à íu
	offset_position_ = D3DXVECTOR2(0.0f,0.0f);
	time_ =0;
	__set_time(time_);


	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void ObjectRecord::Uninitialize(void)
{
	for(int i=0;i<TEXTURE_MAX;i++)
	{
		SafeRelease(number_[i]);
	}
}

//=============================================================================
// update
//=============================================================================
void ObjectRecord::Update(void)
{
	for(int i=0;i<TEXTURE_MAX;i++)
	{
		number_[i]->Update();
	}
}

//=============================================================================
// draw
//=============================================================================
void ObjectRecord::Draw(void)
{
	for(int i=0;i<TEXTURE_MAX;i++)
	{
		number_[i]->Draw();
	}
}


void ObjectRecord::__set_time(u32 time)
{
	if(time == 65535)
	{
		for(int i=0;i<TEXTURE_MAX;i++)
		{
			number_[i]->__Set_index(10);
		}
		//Ç±ÇÎÇÒ
		number_[2]->__Set_index(11);
		//dotto
		number_[5]->__Set_index(12);
	}
	else if(time >= 0)
	{
		time_=time;
		//
		u32 workA=0;
		f32 workB=0;

		u32 min=0;
		u32 sec=0;
		u32 mlisec=0;

		workA = time_;

		//É~ÉäïbÇÇæÇ∑
		mlisec=workA%60;
		workA-=mlisec;
		workA /= 60;
		//ïbÇäÑÇËèoÇ∑
		sec = workA%60;
		workA -= sec;
		workA/=60;
		//Ç”ÇÒÇäÑÇËèoÇ∑
		min=workA;

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

		//Ç±ÇÎÇÒ
		number_[2]->__Set_index(11);

		workA = sec;
		//ïbÅ@ÇPÇOÇÃà 
		workB = (f32)(workA%10);
		number_[4]->__Set_index((u32)workB);
		workA -= (u32)workB;
		workA /= 10;

		//ïbÅ@ÇPÇÃà 
		workB = (f32)(workA%10);
		number_[3]->__Set_index((u32)workB);
		workA -= (u32)workB;
		workA /= 10;

		//dotto
		number_[5]->__Set_index(12);

		workA = mlisec * 100 / 60;
		//ïbÅ@ÇPÇOÇÃà 
		workB = (f32)(workA%10);
		number_[7]->__Set_index((u32)workB);
		workA -= (u32)workB;
		workA /= 10;

		//ïbÅ@ÇPÇÃà 
		workB = (f32)(workA%10);
		number_[6]->__Set_index((u32)workB);
		workA -= (u32)workB;
		workA /= 10;
	}
	else
	{
		for(int i=0;i<TEXTURE_MAX;i++)
		{
			number_[i]->__Set_index(10);
		}
		//Ç±ÇÎÇÒ
		number_[2]->__Set_index(11);
		//dotto
		number_[5]->__Set_index(12);
	}
}

//=============================================================================
// set pos
//=============================================================================
void ObjectRecord::__set_position(D3DXVECTOR2 pos)
{
	for(int i=0;i<TEXTURE_MAX;i++)
	{
		number_[i]->__Set_position(D3DXVECTOR2((f32)35*i+(pos.x-125),pos.y));
	}
}

void  ObjectRecord::__offset_position(const D3DXVECTOR2& offset_position)
{
	offset_position_ = offset_position; 
	for(int i=0;i<TEXTURE_MAX;i++)
	{
		number_[i]->__offset_position(offset_position_);
	}

}


//---------------------------------- EOF --------------------------------------
