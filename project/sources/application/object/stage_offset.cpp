//*****************************************************************************
//
// stage offset
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include"stage_offset.h"
#include "system/system.h"

static const D3DXVECTOR2 POSITION_MOVE_RATE = D3DXVECTOR2(0.155f, 0.16f);

//=============================================================================
// constructor
//=============================================================================
StageOffset::StageOffset(void)
	:position_(0.0f,0.0f)
	,target_position_(0.0f,0.0f)
	,stage_size_(0.0f,0.0f)
	,reference_position_(0.0f,0.0f)
	,screen_size_(0.0f,0.0f)
{
}

//=============================================================================
// destructor
//=============================================================================
StageOffset::~StageOffset(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool StageOffset::Initialize(void)
{
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void StageOffset::Uninitialize(void)
{
}

//=============================================================================
// update
//=============================================================================
void StageOffset::Update(void)
{
	target_position_.x = reference_position_.x - screen_size_.x * 0.5f;
	target_position_.y = reference_position_.y - screen_size_.y * 0.5f;

	position_.x += (target_position_.x - position_.x) * POSITION_MOVE_RATE.x;
	position_.y += (target_position_.y - position_.y) * POSITION_MOVE_RATE.y;

	if(position_.x < 0.0f)
	{
		position_.x = 0.0f;
	}

	if(position_.x > stage_size_.x - screen_size_.x)
	{
		position_.x = stage_size_.x - screen_size_.x;
	}

	if(position_.y < 0.0f)
	{
		position_.y = 0.0f;
	}

	if(position_.y > stage_size_.y - screen_size_.y)
	{
		position_.y = stage_size_.y - screen_size_.y;
	}

}

//---------------------------------- EOF --------------------------------------
