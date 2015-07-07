//*****************************************************************************
//
// record
//
// Author	: masato masuda
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "record.h"
#include "system/system.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const u32 CLEAR_NUMBER = 0;

//=============================================================================
// constructor
//=============================================================================
Record::Record(void)
	: stage_num_(0)
	, record_(nullptr)
{
}

//=============================================================================
// destructor
//=============================================================================
Record::~Record(void)
{
	delete[] record_;
	record_ = nullptr;
}

//=============================================================================
// initialize
//=============================================================================
bool Record::Initialize(void)
{
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void Record::Uninitialize(void)
{
}

//=============================================================================
// __record(getter)
//-----------------------------------------------------------------------------
// エラーの時は-1が変えるよ
//=============================================================================
s32 Record::__record(const u32 stage_num)
{
	// error
	if(record_ == nullptr) return -1;
	if(stage_num < 0 && stage_num >= stage_num_) return -1;

	return record_[stage_num];
}

//=============================================================================
// __record(setter)
//-----------------------------------------------------------------------------
// エラーの時はfalseになるよ
//=============================================================================
bool Record::__record(const u32 stage_num, const u32 record)
{
	// error
	if(record_ == nullptr) return false;
	if(stage_num < 0 && stage_num >= stage_num_) return false;

	record_[stage_num] = record;
	return true;
}

//=============================================================================
// LoadFile
//=============================================================================
bool Record::LoadFile(const s8* file_name)
{
	FILE* file = nullptr;

	fopen_s(&file,file_name,"rb");

	if(file == nullptr)
	{
		return false;
	}

	// ステージ数読込
	fread(&stage_num_, sizeof(u32), 1, file);

	if(stage_num_ <= 0)
	{
		return false;
	}

	// レコード数生成
	record_ = new u32[ stage_num_ ];
	memset(record_, 0, sizeof(record_));

	// レコード読込
	for(u32 i = 0 ; i < stage_num_ ; i++)
	{
		fread(&record_[i], sizeof(u32), 1, file);
	}

	fclose(file);

	return true;
}

//=============================================================================
// SaveFile
//=============================================================================
bool Record::SaveFile(const s8* file_name)
{
	FILE* file = nullptr;

	fopen_s(&file,file_name,"wb");

	if(file == nullptr)
	{
		return false;
	}

	// ステージ数保存
	fwrite(&stage_num_, sizeof(u32), 1, file);

	// レコード保存
	for(u32 i = 0; i < stage_num_ ; i++)
	{
		fwrite(&record_[i], sizeof(u32), 1, file);
	}

	fclose(file);

	return true;
}

//=============================================================================
// SaveFileClear
//=============================================================================
bool Record::SaveFileClear(const s8* file_name, const u32 stage_num)
{
	FILE* file = nullptr;

	fopen_s(&file,file_name,"wb");

	if(file == nullptr)
	{
		return false;
	}

	// ステージ数保存
	fwrite(&stage_num, sizeof(u32), 1, file);

	// レコード保存
	for(u32 i = 0; i < stage_num ; i++)
	{
		const u32 record = CLEAR_NUMBER;
		fwrite(&record, sizeof(u32), 1, file);
	}

	fclose(file);

	return true;
}


//---------------------------------- EOF --------------------------------------
