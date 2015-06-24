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
	//����
	for(int i=0;i<TEXTURE_MAX;i++)
	{
		number_[i] = new Number();
		number_[i] -> Initialize();
		number_[i] ->__Set_position(D3DXVECTOR2((f32)35*i+680,500));
	}
	//�w�i
	record_back_ = new RecordBack();
	record_back_->Initialize();

	//�ʒu
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
		number_[i] ->__Set_position(D3DXVECTOR2(35*i+680 + offset_position_.x,500));
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

	//�~���b������
	mlisec = workA % 60;
	workA = workA / 60;
	//�b������o��
	sec = workA%60;
	workA = sec / 60;
	//�b�������ĕ��݂̂ɂ���
	min=workA%60;

	workA = min;
	//���@�P�O�̈�
	workB = (f32)(workA%10);
	number_[1]->__Set_index((u32)workB);
	workA -= (u32)workB;
	workA /= 10;

	//���@�P�̈�
	workB = (f32)(workA%10);
	number_[0]->__Set_index((u32)workB);
	workA -= (u32)workB;
	workA /= 10;

	//�����
	number_[2]->__Set_index(11);

	workA = sec;
	//�b�@�P�O�̈�
	workB = (f32)(workA%10);
	number_[4]->__Set_index((u32)workB);
	workA -= (u32)workB;
	workA /= 10;

	//�b�@�P�̈�
	workB = (f32)(workA%10);
	number_[3]->__Set_index((u32)workB);
	workA -= (u32)workB;
	workA /= 10;

	//dotto
	number_[5]->__Set_index(12);

	workA = mlisec;
	//�b�@�P�O�̈�
	workB = (f32)(workA%10);
	number_[7]->__Set_index((u32)workB);
	workA -= (u32)workB;
	workA /= 10;

	//�b�@�P�̈�
	workB = (f32)(workA%10);
	number_[6]->__Set_index((u32)workB);
	workA -= (u32)workB;
	workA /= 10;

}

//---------------------------------- EOF --------------------------------------
