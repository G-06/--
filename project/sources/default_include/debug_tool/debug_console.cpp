//*****************************************************************************
//
// debug console
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "debug_console.h"

//*****************************************************************************
// macro definition
//*****************************************************************************

//*****************************************************************************
// constant definition
//*****************************************************************************
const s8* DebugConsole::CAPTION = "debug console";

//=============================================================================
// constructor
//=============================================================================
DebugConsole::DebugConsole(void):
is_show_(true)
{
#ifndef _RELEASE
	memset(string_,0,STRING_MAX);
#endif
}

//=============================================================================
// destructor
//=============================================================================
DebugConsole::~DebugConsole(void)
{
#ifndef _RELEASE
#endif
}

//=============================================================================
// initialize
//=============================================================================
bool DebugConsole::Initialize(void)
{
#ifndef _RELEASE
	SMALL_RECT small_rect = {0,0,80,25};
	COORD coord={80,25};

	// コンソールの作成
	AllocConsole();

	// コンソールウィンドウのタイトル
	SetConsoleTitle(CAPTION);

	// コンソールウィンドウハンドルの取得
	hwnd_ = GetConsoleWindow();

	// バッファサイズの設定
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),coord);

	// ウィンドウサイズの設定
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE),TRUE,&small_rect);

	// 書き込み用ファイルパス
	//sprintf(log_file_path_,"log/%d.txt",time(NULL));
#endif
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void DebugConsole::Uninitialize(void)
{
#ifndef _RELEASE
	FreeConsole();
#endif
}

//=============================================================================
// update
//=============================================================================
void DebugConsole::Update(void)
{
#ifndef _RELEASE
#endif
}

//=============================================================================
// draw
//=============================================================================
void DebugConsole::Draw(void)
{
#ifndef _RELEASE
	DWORD op;

	// draw
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE),string_,strlen(string_),&op,NULL);

	// clear
	memset(string_,'\0',sizeof(string_));

#endif
}

//=============================================================================
// 表示
//=============================================================================
void DebugConsole::Show(void)
{
#ifndef _RELEASE
	ShowWindow(hwnd_,SW_SHOW);
	is_show_ = true;
#endif
}

//=============================================================================
// 非表示
//=============================================================================
void DebugConsole::Hide(void)
{
#ifndef _RELEASE
	ShowWindow(hwnd_,SW_HIDE);
	is_show_ = false;
#endif
}

//=============================================================================
// 表示切り換え
//=============================================================================
void DebugConsole::SwitchWindow(void)
{
#ifndef _RELEASE
	if(is_show_)
	{
		Hide();
	}
	else
	{
		Show();
	}
#endif
}

//=============================================================================
// print
//=============================================================================
void DebugConsole::Print(const s8* format,...)
{
#ifndef _RELEASE
	char work[STRING_MAX] = {NULL};
	va_list args;

	// 可変引数の参照開始
	va_start(args,format);

	// 文字列に変更
	vsprintf(work,format,args);

	// 可変引数の参照終了
	va_end(args);

	// ログに書込
	strcat(string_,work);
#endif
}

//-----------------------------------EOF---------------------------------------
