//*****************************************************************************
//
// main
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "main.h"
#include "application/application.h"
#include "system/system.h"

//=============================================================================
// エントリーポイント
//=============================================================================
int APIENTRY WinMain(HINSTANCE hinstance, HINSTANCE preview_hinstance, LPSTR command_line,int command_show)
{
#ifndef _RELEASE
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _RELEASE

	// HACK とりあえず無いとウイルスになる
	FILE* file = nullptr;
	fopen_s(&file,"framework.exe","rb");
	fclose(file);

	// setup system
	if(!System::Setup(hinstance))
	{
		MessageBox(GET_SYSTEM.__window()->__hwnd(),"failed setup system","error",MB_ICONERROR);

		// shutdown system
		System::Shutdown();

		return 0;
	}


	if(!DebugTool::Setup())
	{
		ASSERT("failed setup debug tool");
	}

	// create application
	Application* application = new Application();

	// initialize application
	if(!SafeInitialize(application))
	{
		MessageBox(GET_SYSTEM.__window()->__hwnd(),"failed initialize application","error",MB_ICONERROR);

		// release application
		SafeRelease(application);

		// shutdown system
		System::Shutdown();

		return 0;
	}

	// update application
	application->Update();

	// release application
	SafeRelease(application);

	// shutdown debug tool
	DebugTool::Shutdown();

	// shutdown system
	System::Shutdown();

	return 0;
}

//---------------------------------- EOF --------------------------------------
