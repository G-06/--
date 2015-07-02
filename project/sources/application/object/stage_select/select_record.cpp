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
#include "system/system.h"
#include "../object_record.h"
#include "select_record_back.h"

static const D3DXVECTOR2 DEFAULT_POS_NUM(680.f,450.f);		// デフォルトポジション 数字の一番左端の位置

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
	record_ = new ObjectRecord();
	record_ ->Initialize();

	back_ = new RecordBack();
	back_->Initialize();

	off_position_ = D3DXVECTOR2(0.0f,0.0f);

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void SelectRecord::Uninitialize(void)
{
	SafeRelease(record_);
	SafeRelease(back_);
}

//=============================================================================
// update
//=============================================================================
void SelectRecord::Update(void)
{
	record_->__offset_position(off_position_);
	back_->__offset_position(off_position_);

	record_->Update();
	back_->Update();
}

//=============================================================================
// draw
//=============================================================================
void SelectRecord::Draw(void)
{
	back_->Draw();
	record_->Draw();
}

void SelectRecord::__set_time(u32 time)
{
	record_->__set_time(time);
}

void SelectRecord::__set_position(D3DXVECTOR2 pos)
{
	record_->__set_position(pos);
	back_->__Set_position(pos);
}


//---------------------------------- EOF --------------------------------------
