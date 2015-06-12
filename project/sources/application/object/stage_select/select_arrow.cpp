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
#include "select_arrow.h"
#include "select_arrow_left.h"
#include "select_arrow_right.h"
#include "render/sprite.h"
#include "system/system.h"

//=============================================================================
// constructor
//=============================================================================
SelectArrow::SelectArrow(void)
{
}

//=============================================================================
// destructor
//=============================================================================
SelectArrow::~SelectArrow(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool SelectArrow::Initialize(void)
{
	//
	arrow_right_ = new ArrowRight();
	arrow_right_->Initialize();

	//
	arrow_left_ = new ArrowLeft();
	arrow_left_ ->Initialize();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void SelectArrow::Uninitialize(void)
{
	SafeRelease(arrow_right_);
	SafeRelease(arrow_left_);
}

//=============================================================================
// update
//=============================================================================
void SelectArrow::Update(void)
{
	if(stage_id_ == 0)
	{
		arrow_left_->__Alpha_Off();
		arrow_right_->Update();
	}
	else if(stage_id_ == 2-1)
	{
		arrow_right_->__Alpha_Off();
		arrow_left_->Update();
	}
	else
	{
		//arrow_left_->__Alpha_On();
		//arrow_right_->__Alpha_On();
		arrow_left_->Update();
		arrow_right_->Update();
	}
}

//=============================================================================
// draw
//=============================================================================
void SelectArrow::Draw(void)
{
	arrow_right_->Draw();
	arrow_left_->Draw();
}

//---------------------------------- EOF --------------------------------------
