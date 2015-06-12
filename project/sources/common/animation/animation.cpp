//*****************************************************************************
//
// animation
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "animation.h"

//=============================================================================
// constructor
//=============================================================================
Animation::Animation(void)
	:frame_count_(0)
	,current_index_(0)
	,number_(0)
	,is_actitive_(false)
	,is_end_(false)
{
}

//=============================================================================
// destructor
//=============================================================================
Animation::~Animation(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool Animation::Initialize(void)
{
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void Animation::Uninitialize(void)
{
}

//=============================================================================
// update
//=============================================================================
void Animation::Update(void)
{
	if(is_actitive_)
	{
		if(current_index_ >= 0 && current_index_ < container_.size())
		{
			frame_count_++;

			if(frame_count_ >= container_[current_index_]._frame)
			{
				if(current_index_ == container_[current_index_]._next_index)
				{
					is_end_ = true;
				}
				current_index_ = container_[current_index_]._next_index;
				number_ = container_[current_index_]._number;
				frame_count_ = 0;
			}
		}
	}
}

//=============================================================================
// add
//=============================================================================
void Animation::Add(const DATA* data,u32 size)
{
	for(u32 i = 0;i < size;++i)
	{
		container_.push_back(*(data + i));
	}
}

//=============================================================================
// start
//=============================================================================
void Animation::Start(u32 index)
{
	is_actitive_ = true;
	is_end_ = false;
	current_index_ = index;
}

//=============================================================================
// stop
//=============================================================================
void Animation::Stop(void)
{
	is_actitive_ = false;
	is_end_ = false;
}

//=============================================================================
// clear
//=============================================================================
void Animation::Clear(void)
{
	frame_count_ = 0;
	current_index_ = 0;
	number_ = 0;
	is_actitive_ = false;
	is_end_ = false;
	container_.clear();
}

//---------------------------------- EOF --------------------------------------
