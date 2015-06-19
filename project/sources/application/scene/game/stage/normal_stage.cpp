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
#include "../gimmick/gimmick_obstacle.h"
#include "../gimmick/gimmick_disappear_ground.h"
#include "../gimmick/gimmick_move_ground.h"

#include "../gimmick/gimmick_tutorial_text.h"


#include "object/object_light_gauge.h"
#include "collision/collision_map.h"

//=============================================================================
// constructor
//=============================================================================
NormalStage::NormalStage(const TYPE& type)
	:Stage(type)
	,is_pause_(false)
	,is_clear_(false)
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

	SafeDelete(next_stage_factory_);
}

//=============================================================================
// update
//=============================================================================
void NormalStage::Update(void)
{
	if(game_player_->__life() < 0)
	{
		if(next_stage_factory_ == nullptr)
		{
			next_stage_factory_ = new SelectFactory();
		}
	}
	else
	{
		if(is_pause_)
		{
		}
		else
		{
			time_count_++;

			game_player_->Update();

			for(auto it = gimmick_container_.begin();it != gimmick_container_.end();++it)
			{
				(*it)->Update();
			}

			object_light_gauge_->__rate((f32)game_player_->__sp() / (f32)game_player_->__sp_max() * 100.0f);

			object_light_gauge_->Update();

			if(game_player_->__position().y > map_->__size().y)
			{
				game_player_->Dead();
			}

			CollisionGimmick();
			CollisionChip();

			// offset
			stage_offset_->__reference_position(game_player_->__position());
			stage_offset_->Update();

			game_player_->__offset_position(stage_offset_->__position());

			map_->__position(-stage_offset_->__position());

			for(auto it = gimmick_container_.begin();it != gimmick_container_.end();++it)
			{
				(*it)->__offset_position(stage_offset_->__position());
			}

			if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_P))
			{
				next_scene_factory_ = new TitleFactory();
			}
		}
	}

#ifndef _RELEASE
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_R))
	{
		Uninitialize();
		Initialize();
	}
#endif
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
// collision chip
//=============================================================================
void NormalStage::CollisionChip(void)
{
	D3DXVECTOR2 player_position = game_player_->__position();
	D3DXVECTOR2 player_old_position = game_player_->__old_position();
	D3DXVECTOR2 index_position;
	u32 index = 0;
	CollisionMap collision_map;

	// 下
	index = map_->GetIndex(D3DXVECTOR2(player_position.x,player_position.y + game_player_->__size().y * 0.5f),&index_position);

	CollisionChip(index,index_position);

	// 右
	index = map_->GetIndex(D3DXVECTOR2(player_position.x + game_player_->__size().x * 0.5f,player_position.y),&index_position);

	CollisionChip(index,index_position);

	// 左
	index = map_->GetIndex(D3DXVECTOR2(player_position.x - game_player_->__size().x * 0.5f,player_position.y),&index_position);

	CollisionChip(index,index_position);

	// 上
	index = map_->GetIndex(D3DXVECTOR2(player_position.x,player_position.y - game_player_->__size().y * 0.5f),&index_position);

	CollisionChip(index,index_position);

	// 右下
	index = map_->GetIndex(D3DXVECTOR2(player_position.x + game_player_->__size().x * 0.5f,player_position.y + game_player_->__size().y * 0.5f),&index_position);

	CollisionChip(index,index_position);

	// 左下
	index = map_->GetIndex(D3DXVECTOR2(player_position.x - game_player_->__size().x * 0.5f,player_position.y + game_player_->__size().y * 0.5f),&index_position);

	CollisionChip(index,index_position);

	// 右上
	index = map_->GetIndex(D3DXVECTOR2(player_position.x + game_player_->__size().x * 0.5f,player_position.y - game_player_->__size().y * 0.5f),&index_position);

	CollisionChip(index,index_position);

	// 左上
	index = map_->GetIndex(D3DXVECTOR2(player_position.x - game_player_->__size().x * 0.5f,player_position.y - game_player_->__size().y * 0.5f),&index_position);

	CollisionChip(index,index_position);

}

//=============================================================================
// collision chip
//=============================================================================
void NormalStage::CollisionChip(u32 index,const D3DXVECTOR2& position)
{
	CollisionMap collision_map;

	switch(index)
	{
		case 1:
		{
			if(collision_map.IsHit(game_player_->__position(),game_player_->__old_position(),position,game_player_->__size().x * 0.5f,game_player_->__size().y * 0.5f,128 * 0.5f,128 * 0.5f))
			{
				if(game_player_->__is_preview_light())
				{
					game_player_->Dead();
				}
				else
				{
					if(collision_map.__vector().y > 0)
					{
						game_player_->HitStage(collision_map.__position(),true);
					}
					else
					{
						game_player_->HitStage(collision_map.__position());
					}
				}
			}
			break;
		}
		case 2:
		{
			if(collision_map.IsHit(game_player_->__position(),game_player_->__old_position(),position,game_player_->__size().x * 0.5f,game_player_->__size().y * 0.5f,128 * 0.5f,128 * 0.5f))
			{
				if(game_player_->__is_light())
				{
					if(collision_map.__vector().x != 0.0f)
					{
						game_player_->ChangeDirection(D3DXVECTOR2(-game_player_->__move().x,game_player_->__move().y));
					}
					else
					{
						game_player_->ChangeDirection(D3DXVECTOR2(game_player_->__move().x,-game_player_->__move().y));
					}
				}
				else
				{
					if(collision_map.__vector().y > 0)
					{
						game_player_->HitStage(collision_map.__position(),true);
					}
					else
					{
						game_player_->HitStage(collision_map.__position());
					}
				}
			}
			break;
		}
		case 3:
		{
			if(collision_map.IsHit(game_player_->__position(),game_player_->__old_position(),position,game_player_->__size().x * 0.5f,game_player_->__size().y * 0.5f,128 * 0.5f,128 * 0.5f))
			{
				if(game_player_->__is_light())
				{
					game_player_->__is_force_light(true);
				}
				else
				{
					if(collision_map.__vector().y > 0)
					{
						game_player_->HitStage(collision_map.__position(),true);
					}
					else
					{
						game_player_->HitStage(collision_map.__position());
					}
				
				}
			}
			break;
		}
		case 4:
		{
			if(collision_map.IsHit(game_player_->__position(),game_player_->__old_position(),position,game_player_->__size().x * 0.5f,game_player_->__size().y * 0.5f,128 * 0.5f,128 * 0.5f))
			{
				game_player_->Dead();
			}
			break;
		}
		case 5:
		{
			if(collision_map.IsHit(game_player_->__position(),game_player_->__old_position(),position,game_player_->__size().x * 0.5f,game_player_->__size().y * 0.5f,128 * 0.5f,128 * 0.5f))
			{
				//game_player_->Dead();
			}
			break;
		}
		case 6:
		{
			if(collision_map.IsHit(game_player_->__position(),game_player_->__old_position(),position,game_player_->__size().x * 0.5f,game_player_->__size().y * 0.5f,128 * 0.5f,128 * 0.5f))
			{
				//game_player_->Dead();
			}
			break;
		}
		default:
		{
			break;
		}
	}
}

//=============================================================================
// collision gimmick
//=============================================================================
void NormalStage::CollisionGimmick(void)
{
	for(auto it = gimmick_container_.begin();it != gimmick_container_.end();++it)
	{
		D3DXVECTOR2 player_position = game_player_->__position();
		D3DXVECTOR2 player_old_position = game_player_->__old_position();
		D3DXVECTOR2 player_size = game_player_->__size() * 0.5f;
		D3DXVECTOR2 gimmick_position = (*it)->__position();
		D3DXVECTOR2 gimmick_size = (*it)->__size() * 0.5f;
		CollisionMap collision_map;

		if(collision_map.IsHit(player_position,player_old_position,gimmick_position,player_size.x,player_size.y,gimmick_size.x,gimmick_size.y))
		{
			switch((*it)->__type())
			{
				case Gimmick::TYPE_CHECK_POINT:
				{
					DEBUG_TOOL.__debug_display()->Print("hit check point\n");
					GimmickCheckPoint::DATA* data = (GimmickCheckPoint::DATA*)(*it)->GetPointer();
					if(game_player_->__check_point_priority() < data->_priority)
					{
						game_player_->__check_point_priority(data->_priority);
						game_player_->__return_position(gimmick_position);
					}
					break;
				}
				case Gimmick::TYPE_GOAL_POINT:
				{
					DEBUG_TOOL.__debug_display()->Print("hit goal point\n");
					game_player_->Clear();
					is_clear_ = true;
					break;
				}
				case Gimmick::TYPE_OBSTACLE:
				{
					DEBUG_TOOL.__debug_display()->Print("hit obstacle\n");
					game_player_->Dead();
					break;
				}
				case Gimmick::TYPE_DISAPPEAR_GROUND:
				{
					GimmickDisappearGround::DATA* data = (GimmickDisappearGround::DATA*)(*it)->GetPointer();
					if(data->_is_hit)
					{
						DEBUG_TOOL.__debug_display()->Print("hit disappear ground\n");
						if(collision_map.__vector().y > 0)
						{
							game_player_->HitStage(collision_map.__position(),true);
						}
						else
						{
							game_player_->HitStage(collision_map.__position(),false);
						}
					}
					break;
				}
				case Gimmick::TYPE_MOVE_GROUND:
				{
					GimmickMoveGround::DATA* data = (GimmickMoveGround::DATA*)(*it)->GetPointer();

					if(collision_map.IsHit(player_position,player_old_position + data->_move,gimmick_position,player_size.x,player_size.y,gimmick_size.x,gimmick_size.y))
					{
						if(collision_map.__vector().y > 0)
						{
							game_player_->Accelerate(data->_move);
							game_player_->HitStage(collision_map.__position(),true);
						}
						else
						{
							game_player_->HitStage(collision_map.__position());
						}
						DEBUG_TOOL.__debug_display()->Print("hit move ground\n");
					}
					break;
				}
				case Gimmick::TYPE_TUTORIAL_TEXT:
				{
					GimmickTutorialText::DATA* data = (GimmickTutorialText::DATA*)(*it)->GetPointer();
					if(data->_is_hit)
					{
						DEBUG_TOOL.__debug_display()->Print("hittxt\n");
						data->_priority=0;

					break;
					}
				}
			}
		}
	}
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
					i++;
					i += FindWord(word,&data[i],",\n\0");
					u32 priority = atoi(word);

					GimmickCheckPoint* gimmick = new GimmickCheckPoint();
					gimmick->Initialize();
					gimmick->__position(D3DXVECTOR2(x,y));
					gimmick->__priority(priority);
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
				case Gimmick::TYPE_OBSTACLE:
				{
					i += FindWord(word,&data[i],",\n\0");
					f32 x = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					f32 y = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					f32 end_x = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					f32 end_y = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					f32 speed = atof(word);

					GimmickObstacle* gimmick = new GimmickObstacle();
					gimmick->Initialize();
					gimmick->__position(D3DXVECTOR2(x,y));
					gimmick->__start_position(D3DXVECTOR2(x,y));
					gimmick->__end_position(D3DXVECTOR2(end_x,end_y));
					gimmick->__speed(speed);
					gimmick_container_.push_back(gimmick);
					i += FindWord(word,&data[i],"\n\0");
					break;
				}
				case Gimmick::TYPE_DISAPPEAR_GROUND:
				{
					i += FindWord(word,&data[i],",\n\0");
					f32 x = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					f32 y = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					u32 appear_frame = atoi(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					u32 disappear_frame = atoi(word);

					GimmickDisappearGround* gimmick = new GimmickDisappearGround();
					gimmick->Initialize();
					gimmick->__position(D3DXVECTOR2(x,y));
					gimmick->__appear_frame(appear_frame);
					gimmick->__disappear_frame(disappear_frame);
					gimmick_container_.push_back(gimmick);
					i += FindWord(word,&data[i],"\n\0");
					break;
				}
				case Gimmick::TYPE_MOVE_GROUND:
				{
					i += FindWord(word,&data[i],",\n\0");
					f32 x = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					f32 y = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					f32 end_x = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					f32 end_y = atof(word);
					i++;
					i += FindWord(word,&data[i],",\n\0");
					f32 speed = atof(word);

					GimmickMoveGround* gimmick = new GimmickMoveGround();
					gimmick->Initialize();
					gimmick->__position(D3DXVECTOR2(x,y));
					gimmick->__start_position(D3DXVECTOR2(x,y));
					gimmick->__end_position(D3DXVECTOR2(end_x,end_y));
					gimmick->__speed(speed);
					gimmick_container_.push_back(gimmick);
					i += FindWord(word,&data[i],"\n\0");
					break;
				}
				case Gimmick::TYPE_TUTORIAL_TEXT:
				{
					//みる
					i += FindWord(word,&data[i],",\n\0");
					//xを文字列からfloatに
					f32 x = atof(word);
					//次へ
					i++;
					//みる
					i += FindWord(word,&data[i],",\n\0");
					//yを文字列からfloatに
					f32 y = atof(word);
					i++;
					//プライオリティ
					i += FindWord(word,&data[i],",\n\0");
					u32 priority = atoi(word);

					GimmickTutorialText* gimmick = new GimmickTutorialText();
					gimmick->Initialize();
					gimmick->__position(D3DXVECTOR2(x,y));

					//無いと死ぬ
					gimmick_container_.push_back(gimmick);
					i += FindWord(word,&data[i],"\n\0");

					break;
				}
				default:
				{
					i += FindWord(word,&data[i],"\n\0");
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
