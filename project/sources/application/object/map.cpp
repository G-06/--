//*****************************************************************************
//
// map
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "map.h"
#include "render/mesh_sprite.h"
#include "system/system.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 Map::SIZE		= D3DXVECTOR2(128.0f,128.0f);
const u32 Map::DIVISION_WIDTH	= 2;
const u32 Map::DIVISION_HEIGHT	= 2;

//=============================================================================
// constructor
//=============================================================================
Map::Map(void)
	:map_(nullptr)
	,indexs_(nullptr)
	,position_(0.0f,0.0f)
	,size_(0.0f,0.0f)
{
}

//=============================================================================
// destructor
//=============================================================================
Map::~Map(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool Map::Initialize(void)
{
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void Map::Uninitialize(void)
{
	SafeDeleteArray(indexs_);

	SafeRelease(map_);
}

//=============================================================================
// update
//=============================================================================
void Map::Update(void)
{
}

//=============================================================================
// draw
//=============================================================================
void Map::Draw(void)
{
	if(map_ != nullptr)
	{
		GET_DIRECTX9_DEVICE->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_CLAMP);
		GET_DIRECTX9_DEVICE->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_CLAMP);
		GET_DIRECTX9_DEVICE->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_NONE);
		GET_DIRECTX9_DEVICE->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_NONE);
		map_->__position(position_);
		map_->Draw();
		GET_DIRECTX9_DEVICE->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
		GET_DIRECTX9_DEVICE->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
		GET_DIRECTX9_DEVICE->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_WRAP);
		GET_DIRECTX9_DEVICE->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_WRAP);
	}
}

//=============================================================================
// get index
//=============================================================================
u32 Map::GetIndex(const D3DXVECTOR2& position,D3DXVECTOR2* index_position)
{
	s32 index_x = (s32)(position.x / SIZE.x);
	s32 index_y = (s32)(position.y / SIZE.y);
	s32 index = index_y * width_ + index_x;

	if(index_x < 0 || index_x >= width_ || index_y < 0 || index_y >= height_)
	{
		return 0;
	}

	if(index_position != nullptr)
	{
		index_position->x = SIZE.x * index_x + SIZE.x * 0.5f + 0.5f;
		index_position->y = SIZE.y * index_y + SIZE.y * 0.5f + 0.5f;
	}

	return indexs_[index];
}

//=============================================================================
// load from file
//=============================================================================
bool Map::LoadFromFile(const s8* filename)
{
	u8* data;
	FILE* file = nullptr;
	u32 size;

	fopen_s(&file,filename,"rb");

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
bool Map::LoadFromMemory(const u8* memory)
{
	u32 offset = 0;

	memcpy(&width_,memory + offset,sizeof(u32));
	offset += sizeof(u32);
	memcpy(&height_,memory + offset,sizeof(u32));
	offset += sizeof(u32);
	indexs_ = new u32[width_ * height_];
	memcpy(indexs_,memory + offset,sizeof(u32) * width_ * height_);

	size_ = D3DXVECTOR2(width_ * SIZE.x,height_ * SIZE.y);
	map_ = new MeshSprite(width_,height_);
	map_->Initialize();
	map_->__width(SIZE.x);
	map_->__height(SIZE.y);
	map_->__division_width(DIVISION_WIDTH);
	map_->__division_height(DIVISION_HEIGHT);
	map_->__texture_id(Texture::TEXTURE_ID_MAP_GROUND);

	for(u32 i = 0;i < height_;++i)
	{
		for(u32 j = 0;j < width_;++j)
		{
			map_->SetIndex(j,i,indexs_[i * width_ + j]);
		}
	}

	map_->SetParameter();

	return true;
}

//---------------------------------- EOF --------------------------------------
