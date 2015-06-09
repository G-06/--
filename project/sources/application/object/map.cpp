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

//=============================================================================
// constructor
//=============================================================================
Map::Map(void)
	:map_(nullptr)
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
		map_->Draw();
	}
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

	return LoadFromMemory(data);
}

//=============================================================================
// load from memory
//=============================================================================
bool Map::LoadFromMemory(const u8* memory)
{
	u32 width = 0;
	u32 height = 0;
	u32* indexs = nullptr;
	u32 offset = 0;

	memcpy(&width,memory + offset,sizeof(u32));
	offset += sizeof(u32);
	memcpy(&height,memory + offset,sizeof(u32));
	offset += sizeof(u32);
	indexs = new u32[width * height];
	memcpy(indexs,memory + offset,sizeof(u32) * width * height);

	map_ = new MeshSprite(width,height);
	map_->Initialize();
	map_->__width(128);
	map_->__height(128);
	map_->__division_width(2);
	map_->__division_height(2);
	map_->__texture_id(Texture::TEXTURE_ID_TEST);
	for(u32 i = 0;i < height;++i)
	{
		for(u32 j = 0;j < width;++j)
		{
			map_->SetIndex(j,i,indexs[i * width + j]);
		}
	}

	map_->SetParameter();

	return true;
}

//---------------------------------- EOF --------------------------------------
