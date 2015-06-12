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
	SafeDelete(arrow_right_);
	SafeDelete(arrow_left_);
}

//=============================================================================
// update
//=============================================================================
void SelectArrow::Update(void)
{
	arrow_right_->Update();
	arrow_left_->Update();

}

//=============================================================================
// draw
//=============================================================================
void SelectArrow::Draw(void)
{
	if(stage_id_ == STAGE_ID_0)
	{
		arrow_right_->Draw();
	}
	else if(stage_id_ == STAGE_ID_MAX-1)
	{
		arrow_left_->Draw();
	}
	else
	{
		arrow_right_->Draw();
		arrow_left_->Draw();
	}
}

//---------------------------------- EOF --------------------------------------
