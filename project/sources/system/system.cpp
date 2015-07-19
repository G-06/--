//*****************************************************************************
//
// system
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "system.h"
#include "window/main_window.h"
#include "application/object/record.h"

System System::instance_;
u32 System::current_stage_=1;
Record* System::record_;

//=============================================================================
// constructor
//=============================================================================
System::System(void)
{
}

//=============================================================================
// destructor
//=============================================================================
System::~System(void)
{
}

//=============================================================================
// setup
//=============================================================================
bool System::Setup(HINSTANCE hinstance)
{
	timeBeginPeriod(0);

	// create window
	instance_.window_ = new MainWindow(hinstance);

	// initialize window
	if(!SafeInitialize(instance_.window_))
	{
		return false;
	}

	// create directx9
	instance_.directx9_ = new Directx9(instance_.window_);

	// initialize directx9
	if(!SafeInitialize(instance_.directx9_))
	{
		ASSERT("failed initialize directx9");
		return false;
	}

	// create xaudio2
	instance_.xaudio2_ = new XAudio2();

	// initialize xaudio2
	if(!SafeInitialize(instance_.xaudio2_))
	{
		ASSERT("falied initialize xaudio2");
		return false;
	}

	// create direct input
	instance_.direct_input_ = new DirectInput();

	// initialize direct input
	if(!SafeInitialize(instance_.direct_input_))
	{
		ASSERT("failed initialize direct input");
		return false;
	}

	// load option data
	FILE* file = nullptr;

	file = fopen("data/system/option_data.bin","rb");

	if(file == nullptr)
	{
		instance_.option_data_._se_volume  = 0.8f;
		instance_.option_data_._bgm_volume = 0.8f;
		instance_.option_data_._decide_key = INPUT_EVENT_PAD_6;
		instance_.option_data_._cancel_key = INPUT_EVENT_PAD_5;
		instance_.option_data_._light_key  = INPUT_EVENT_PAD_9;
		instance_.option_data_._pause_key  = INPUT_EVENT_PAD_13;
	}
	else
	{
		instance_.option_data_;
		fread(&instance_.option_data_,sizeof(OPTION_DATA),1,file);
		fclose(file);
	}

	GET_DIRECT_INPUT->RegisterInputEventVertual(INPUT_EVENT_VIRTUAL_DECIDE,instance_.option_data_._decide_key);
	GET_DIRECT_INPUT->RegisterInputEventVertual(INPUT_EVENT_VIRTUAL_CANCEL,instance_.option_data_._cancel_key);
	GET_DIRECT_INPUT->RegisterInputEventVertual(INPUT_EVENT_VIRTUAL_LIGHT,instance_.option_data_._light_key);
	GET_DIRECT_INPUT->RegisterInputEventVertual(INPUT_EVENT_VIRTUAL_PAUSE,instance_.option_data_._pause_key);

	instance_.__xaudio2()->__se()->SetVolume(instance_.option_data_._se_volume);
	instance_.__xaudio2()->__bgm()->SetVolume(instance_.option_data_._bgm_volume);

	//レコード読み込み初期化
	instance_.record_ = new Record();
	instance_.record_->Initialize();
	instance_.record_->LoadFile("data/stage/record.bin");

	return true;
}

//=============================================================================
// shutdown
//=============================================================================
void System::Shutdown(void)
{
	//instance_.record_->SaveFileClear("data/stage/record.bin",11);
	instance_.record_->SaveFile("data/stage/record.bin");

	// release window
	SafeRelease(instance_.window_);

	// release directx9
	SafeRelease(instance_.directx9_);

	// release direct input
	SafeRelease(instance_.direct_input_);

	// release xaudio2
	SafeRelease(instance_.xaudio2_);

	//record
	SafeRelease(instance_.record_);

	timeEndPeriod(0);
}

//=============================================================================
//ファイルの読み込み
//=============================================================================
void System::FileLoad(const s8* file_name)
{
	instance_.record_->LoadFile(file_name);
}

//=============================================================================
//レコード保存
//=============================================================================
void System::RecordSave(const u32 stage_num, const u32 record)
{
	instance_.record_->__record(stage_num,record);
}

//=============================================================================
//レコードロード
//=============================================================================
u32 System::RecordLoad(const u32 stage_num)
{
	return (instance_.record_->__record(stage_num));
}

//=============================================================================
//ファイルセーブ
//=============================================================================
void System::FileSave(const s8* file_name)
{
	instance_.record_->SaveFile(file_name);
}

//=============================================================================
//ファイルクリアしてセーブ
//=============================================================================
void System::FileSaveClear(const s8* file_name, const u32 stage_num)
{
	instance_.record_->SaveFileClear(file_name,stage_num);
}


//-----------------------------------EOF---------------------------------------
