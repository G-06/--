//*****************************************************************************
//
// main window
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "main_window.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const u32 MainWindow::DEFAULT_WIDTH		= DEFAULT_SCREEN_WIDTH;		// 横幅
const u32 MainWindow::DEFAULT_HEIGHT	= DEFAULT_SCREEN_HEIGHT;	// 縦幅
const s8* MainWindow::CLASS_NAME		= "MainWindow";				// クラス名
const s8* MainWindow::CAPTION_NAME		= "framework";				// キャプション名

//=============================================================================
// constructor
//=============================================================================
MainWindow::MainWindow(HINSTANCE in_hinstance)
{
	WNDCLASSEX wndclassex =
	{
		sizeof(WNDCLASSEX),				// 構造体のサイズ
		CS_CLASSDC,						// スタイル
		WindowProcedure,				// プロシージャの関数ポインタ
		0,								// 
		0,								// 
		in_hinstance,					// インスタンス
		NULL,							// アイコン
		LoadCursor(NULL, IDC_ARROW),	// マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),		// 背景色
		NULL,							// メニュー
		CLASS_NAME,						// ウィンドウのクラス名
		NULL							// アイコン
	};

	hinstance_ = in_hinstance;
	wndclassex_ = wndclassex;

	width_ = DEFAULT_WIDTH;
	height_ = DEFAULT_HEIGHT;

	caption_name_ = CAPTION_NAME;
}

//=============================================================================
// destructor
//=============================================================================
MainWindow::~MainWindow(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool MainWindow::Initialize(void)
{
	return Window::Initialize();
}

//=============================================================================
// uninitialize
//=============================================================================
void MainWindow::Uninitialize(void)
{
	Window::Uninitialize();
}

//=============================================================================
// window procedure
//=============================================================================
LRESULT CALLBACK MainWindow::WindowProcedure(HWND in_hwnd, UINT in_message, WPARAM in_wparam, LPARAM in_lparam)
{
	switch(in_message)
	{
	case WM_DESTROY:			// ウィンドウを破棄
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:			// キー入力
		switch(in_wparam)
		{
		case VK_ESCAPE:			// エスケープキー
			// ウィンドウの破棄
			DestroyWindow(in_hwnd);
			break;
		case VK_INSERT:			// インサートキー
			break;
		}
		break;
	case WM_SIZE:
		//PostMessage(in_hwnd,in_message,in_wparam,in_lparam);
		break;
	default:
		break;
	}

	return DefWindowProc(in_hwnd,in_message,in_wparam,in_lparam);
}

//-----------------------------------EOF---------------------------------------
