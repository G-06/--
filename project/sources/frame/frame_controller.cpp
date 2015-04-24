//*****************************************************************************
//
// frame controller
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "frame_controller.h"
#include "system/timer/timer.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const u32 FrameController::DEFAULT_MAX_FRAME = 60;

//=============================================================================
// constructor
//=============================================================================
FrameController::FrameController(void):
timer_(nullptr),
max_frame_(0),
frame_count_(0),
sum_time_(0),
frame_time_(0),
fps_(0)
{
	max_frame_ = DEFAULT_MAX_FRAME;

	frame_time_ = 1000 / max_frame_;
}

//=============================================================================
// destructor
//=============================================================================
FrameController::~FrameController(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool FrameController::Initialize(void)
{
	// create timer
	timer_ = new Timer();

	// initialize timer
	if(!SafeInitialize(timer_))
	{
		return false;
	}

	// start timer
	timer_->Start();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void FrameController::Uninitialize(void)
{
	// release timer
	SafeRelease(timer_);
}

//=============================================================================
// update
//=============================================================================
void FrameController::Update(void)
{
	timer_->Reset();

	if(sum_time_ >= 500)
	{
		fps_ = frame_count_ * 1000 / sum_time_;
		sum_time_ = 0;
		frame_count_ = 0;
	}
}

//=============================================================================
// wait
//=============================================================================
void FrameController::Wait(void)
{
	u32 current_time = timer_->GetTime();

	if(frame_time_ > current_time)
	{
		Sleep(frame_time_ - current_time - 1);
		frame_count_++;
		sum_time_ += timer_->GetTime();
	}
}

//---------------------------------- EOF --------------------------------------
