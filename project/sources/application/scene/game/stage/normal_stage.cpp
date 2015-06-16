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
#include "../gimmick/gimmick_check_point.h"
#include "../gimmick/gimmick_goal_point.h"
#include "object/object_light_gauge.h"
#include "collision/collision_map.h"
#include "object/object_check_point.h"

//=============================================================================
// constructor
//=============================================================================
NormalStage::NormalStage(const TYPE& type)
	:Stage(type)
	,is_pause_(false)
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

	object_light_gauge_ = new ObjectLightGauge();
	object_light_gauge_->Initialize();
	object_light_gauge_->__position(D3DXVECTOR2(100.0f,100.0f));
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

	SafeRelease(object_light_gauge_);

	for(auto it = gimmick_container_.begin();it != gimmick_container_.end();++it)
	{
		SafeRelease(*it);
	}
	gimmick_container_.clear();
}

//=============================================================================
// update
//=============================================================================
void NormalStage::Update(void)
{
	if(is_pause_)
	{
	}
	else
	{
		time_count_++;

		game_player_->Update();

		stage_offset_->__reference_position(game_player_->__position());
		stage_offset_->Update();

		game_player_->__offset_position(stage_offset_->__position());

		map_->__position(-stage_offset_->__position());

		for(auto it = gimmick_container_.begin();it != gimmick_container_.end();++it)
		{
			(*it)->Update();
			(*it)->__offset_position(stage_offset_->__position());
		}

		object_light_gauge_->__rate((f32)game_player_->__sp() / (f32)game_player_->__sp_max() * 100.0f);

		object_light_gauge_->Update();

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

		index = map_->GetIndex(D3DXVECTOR2(player_position.x,player_position.y - game_player_->__size().y * 0.5f),&index_position);

		if(index != 0)
		{
			if(collision_map.IsHit(game_player_->__position(),player_old_position,index_position,game_player_->__size().x * 0.5f,game_player_->__size().y * 0.5f,128 * 0.5f,128 * 0.5f))
			{
				game_player_->HitStage(collision_map.__position(),true);
			}
		}

		index = map_->GetIndex(D3DXVECTOR2(player_position.x,player_position.y + game_player_->__size().y * 0.5f),&index_position);

		if(index != 0)
		{
			if(collision_map.IsHit(game_player_->__position(),player_old_position,index_position,game_player_->__size().x * 0.5f,game_player_->__size().y * 0.5f,128 * 0.5f,128 * 0.5f))
			{
				game_player_->HitStage(collision_map.__position(),true);
			}
		}

		index = map_->GetIndex(D3DXVECTOR2(player_position.x - game_player_->__size().x * 0.5f,player_position.y),&index_position);

		if(index != 0)
		{
			if(collision_map.IsHit(game_player_->__position(),player_old_position,index_position,game_player_->__size().x * 0.5f,game_player_->__size().y * 0.5f,128 * 0.5f,128 * 0.5f))
			{
				game_player_->HitStage(collision_map.__position(),true);
			}
		}

		index = map_->GetIndex(D3DXVECTOR2(player_position.x + game_player_->__size().x * 0.5f,player_position.y),&index_position);

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
}

//=============================================================================
// draw
//=============================================================================
void NormalStage::Draw(void)
{
	map_->Draw();

	for(auto it = gimmick_container_.begin();it != gimmick_container_.end();++it)
	{
		(*it)->Draw();
	}

	game_player_->Draw();
	object_light_gauge_->Draw();
}


//=============================================================================
// load from file
//=============================================================================
bool NormalStage::LoadFromFile(const s8* filename)
{
	s8* data;
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
	data = new s8[size + 1];
	fread(data,1,size,file);
	data[size] = '\n';

	// close file
	fclose(file);

	s8 word[256];
	u32 count = 0;

	for(u32 i = 0;i < size;++i)
	{
		if(data[i] == '/')
		{
			if(data[i + 1] == '/')
			{
				i += FindWord(word,&data[i],"\n");
				count = 0;
			}
		}
		else if(data[i] == ',')
		{
			word[count] = '\0';

			u32 type = atoi(word);
			i++;
			switch(type)
			{
				case Gimmick::TYPE_START_POINT:
				{
					i += FindWord(word,&data[i],",\n\0");
					f32 x = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					f32 y = atof(word);

					GimmickStartPoint* gimmick = new GimmickStartPoint();
					gimmick->Initialize();
					gimmick->__position(D3DXVECTOR2(x,y));
					gimmick_container_.push_back(gimmick);
					game_player_->__position(D3DXVECTOR2(x,y));
					game_player_->__return_position(D3DXVECTOR2(x,y));
					i += FindWord(word,&data[i],"\n\0");
					break;
				}
				case Gimmick::TYPE_CHECK_POINT:
				{
					i += FindWord(word,&data[i],",\n\0");
					f32 x = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					f32 y = atof(word);

					GimmickCheckPoint* gimmick = new GimmickCheckPoint();
					gimmick->Initialize();
					gimmick->__position(D3DXVECTOR2(x,y));
					gimmick_container_.push_back(gimmick);
					i += FindWord(word,&data[i],"\n\0");
					break;
				}
				case Gimmick::TYPE_GOAL_POINT:
				{
					i += FindWord(word,&data[i],",\n\0");
					f32 x = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					f32 y = atof(word);

					GimmickGoalPoint* gimmick = new GimmickGoalPoint();
					gimmick->Initialize();
					gimmick->__position(D3DXVECTOR2(x,y));
					gimmick_container_.push_back(gimmick);
					i += FindWord(word,&data[i],"\n\0");
					break;
				}
				default:
				{
					break;
				}
			}
			count = 0;
		}
		else
		{
			word[count] = data[i];
			count++;
		}
	}

	SafeDeleteArray(data);

	return true;
}

u32 NormalStage::FindWord(s8* dest,const s8* source,s8* words)
{
	u32 count = 0;
	u32 length = strlen(words);

	while(1)
	{
		for(u32 i = 0;i < length;++i)
		{
			if(source[count] == words[i])
			{
				dest[count] = '\0';
				return count;
			}
		}
		dest[count] = source[count];
		count++;
	}
}

//---------------------------------- EOF --------------------------------------
