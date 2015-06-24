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

const f32 StageOffset::OFFSET_MOVE = (0.001f);

//=============================================================================
// constructor
//=============================================================================
StageOffset::StageOffset(void)
	:position_(0.0f,0.0f)
	,stage_size_(0.0f,0.0f)
	,reference_position_(0.0f,0.0f)
	,screen_size_(0.0f,0.0f)
	,old_reference_position_(0.0f, 0.0f)
	,offset_percent_(0.5f, 0.5f)
	,offset_move_(0.0f, 0.0f)
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
	/*bool is_move_x = false;
	bool is_move_y = false;

	if(old_reference_position_.x - reference_position_.x > 0)
	{
		if(offset_percent_.x < 0.55f)
		{
			offset_move_.x = OFFSET_MOVE;
			is_move_x = true;
		}
		else
		{
			offset_move_.x = 0;
		}

	}
	else if(old_reference_position_.x - reference_position_.x < 0)
	{
		if(offset_percent_.x > 0.45f)
		{
			offset_move_.x = -OFFSET_MOVE;
			is_move_x = true;
		}
		else
		{
			offset_move_.x = 0;
		}
	}


	if(old_reference_position_.y - reference_position_.y > 0)
	{
		if(offset_percent_.y > 0.7f)
		{
			offset_move_.y = OFFSET_MOVE*10;
			is_move_y = true;
		}
		else
		{
			offset_move_.y= 0;
		}
	}
	else if(old_reference_position_.y - reference_position_.y < 0)
	{
		if(offset_percent_.y < 0.3f)
		{
			offset_move_.y = -OFFSET_MOVE*10;
			is_move_y = true;
		}
		else
		{
			offset_move_.y = 0;
		}
	}


	if(offset_percent_.x + offset_move_.x < 0.55f
		&& offset_percent_.x + offset_move_.x > 0.45f
		&& is_move_x == true)
	{
		offset_percent_.x += offset_move_.x;
	}

	if(offset_percent_.y + offset_move_.y < 0.7f
		&& offset_percent_.y + offset_move_.y > 0.3f
		&& is_move_y == true)
	{
		offset_percent_.y += offset_move_.y;
	}*/

	position_.x = old_reference_position_.x - screen_size_.x * offset_percent_.x;
	position_.y = old_reference_position_.y - screen_size_.y * offset_percent_.y;


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
