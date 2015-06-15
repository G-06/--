//*****************************************************************************
//
// stage
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "normal_stage.h"
#include "stage_factory.h"
#include "../game_player.h"
#include "object/map.h"
#include "object/stage_offset.h"
#include "../../factory/scene_factory.h"
#include "system/system.h"
#include "../gimmick/gimmick_start_point.h"
#include "collision/collision_map.h"

//=============================================================================
// constructor
//=============================================================================
NormalStage::NormalStage(const TYPE& type)
	:Stage(type)
{
}

//=============================================================================
// destructor
//=============================================================================
NormalStage::~NormalStage(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool NormalStage::Initialize(void)
{
	game_player_ = new GamePlayer();

	if(!SafeInitialize(game_player_))
	{
		return false;
	}
	game_player_->__position(D3DXVECTOR2(100.0f,0.0f));

	stage_offset_ = new StageOffset();

	if(!SafeInitialize(stage_offset_))
	{
		return false;
	}

	stage_offset_->__screen_size(D3DXVECTOR2((f32)DEFAULT_SCREEN_WIDTH,(f32)DEFAULT_SCREEN_HEIGHT));

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void NormalStage::Uninitialize(void)
{
	SafeRelease(game_player_);

	SafeRelease(map_);

	SafeRelease(stage_offset_);
}

//=============================================================================
// update
//=============================================================================
void NormalStage::Update(void)
{
	time_count_++;

	game_player_->Update();

	stage_offset_->__reference_position(game_player_->__position());
	stage_offset_->Update();

	game_player_->__offset_position(stage_offset_->__position());

	map_->__position(-stage_offset_->__position());

	D3DXVECTOR2 player_position = game_player_->__position();
	D3DXVECTOR2 player_old_position = game_player_->__old_position();
	D3DXVECTOR2 index_position;
	u32 index = 0;
	CollisionMap collision_map;

	index = map_->GetIndex(D3DXVECTOR2(player_position.x - game_player_->__size().x * 0.5f,player_position.y - game_player_->__size().y * 0.5f),&index_position);

	if(index != 0)
	{
		if(collision_map.IsHit(game_player_->__position(),player_old_position,index_position,game_player_->__size().x * 0.5f,game_player_->__size().y * 0.5f,128 * 0.5f,128 * 0.5f))
		{
			game_player_->HitStage(collision_map.__position(),true);
		}
	}

	index = map_->GetIndex(D3DXVECTOR2(player_position.x - game_player_->__size().x * 0.5f,player_position.y + game_player_->__size().y * 0.5f),&index_position);

	if(index != 0)
	{
		if(collision_map.IsHit(game_player_->__position(),player_old_position,index_position,game_player_->__size().x * 0.5f,game_player_->__size().y * 0.5f,128 * 0.5f,128 * 0.5f))
		{
			game_player_->HitStage(collision_map.__position(),true);
		}
	}

	index = map_->GetIndex(D3DXVECTOR2(player_position.x + game_player_->__size().x * 0.5f,player_position.y - game_player_->__size().y * 0.5f),&index_position);

	if(index != 0)
	{
		if(collision_map.IsHit(game_player_->__position(),player_old_position,index_position,game_player_->__size().x * 0.5f,game_player_->__size().y * 0.5f,128 * 0.5f,128 * 0.5f))
		{
			game_player_->HitStage(collision_map.__position(),true);
		}
	}

	index = map_->GetIndex(D3DXVECTOR2(player_position.x + game_player_->__size().x * 0.5f,player_position.y + game_player_->__size().y * 0.5f),&index_position);

	if(index != 0)
	{
		if(collision_map.IsHit(game_player_->__position(),player_old_position,index_position,game_player_->__size().x * 0.5f,game_player_->__size().y * 0.5f,128 * 0.5f,128 * 0.5f))
		{
			game_player_->HitStage(D3DXVECTOR2(collision_map.__position().x,collision_map.__position().y),true);
		}
	}

	if(game_player_->__position().y > map_->__size().y)
	{
		game_player_->Dead();
	}

	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_P))
	{
		next_scene_factory_ = new TitleFactory();
	}
}

//=============================================================================
// draw
//=============================================================================
void NormalStage::Draw(void)
{
	game_player_->Draw();

	map_->Draw();
}


//=============================================================================
// load from file
//=============================================================================
bool NormalStage::LoadFromFile(const s8* filename)
{
	u8* data;
	FILE* file = nullptr;
	u32 size;

	fopen_s(&file,filename,"rt");

	if(file == nullptr)
	{
		return false;
	}

	// get file size
	fseek(file,0,SEEK_END);
	size = ftell(file);
	fseek(file,0,SEEK_SET);

	// read data
	data = new u8[size];
	fread(data,1,size,file);

	// close file
	fclose(file);

	LoadFromMemory(data);

	SafeDeleteArray(data);

	return true;
}

//=============================================================================
// load from memory
//=============================================================================
bool NormalStage::LoadFromMemory(const u8* data)
{
	return true;
}

//---------------------------------- EOF --------------------------------------
