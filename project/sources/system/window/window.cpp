//*****************************************************************************
//
// window
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "window.h"
#include "system/thread/thread.h"
#include "system/system.h"

//=============================================================================
// constructor
//=============================================================================
Window::Window(void) :
width_(0),
height_(0),
is_loop_(false),
is_ready_(false),
thread_(nullptr),
hwnd_(NULL)
{
	thread_ = new Thread();
}

//=============================================================================
// destructor
//=============================================================================
Window::~Window(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool Window::Initialize(void)
{
	is_loop_ = false;

	RegisterClassEx(&wndclassex_);

	SafeInitialize(thread_);

	Run();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void Window::Uninitialize(void)
{
	// stop thread
	thread_->Stop();

	// release thread
	SafeRelease(thread_);

	// ウィンドウクラスの登録破棄
	UnregisterClass(wndclassex_.lpszClassName,wndclassex_.hInstance);
}

//=============================================================================
// set window size
//=============================================================================
void Window::SetWindowSize(const u32& in_width,const u32& in_height)
{
	RECT rect =
	{
		0,0,in_width,in_height
	};

	width_ = in_width;
	height_ = in_height;

	AdjustWindowRectEx(&rect,WS_OVERLAPPEDWINDOW,FALSE,0);
	SetWindowPos(hwnd_,NULL,0,0,rect.right - rect.left,rect.bottom - rect.top,SWP_NOMOVE | SWP_NOZORDER);
}

//=============================================================================
// run
//=============================================================================
void Window::Run(void)
{
	// is loop
	is_loop_ = true;

	// is not ready
	is_ready_ = false;

	// start thread
	thread_->Start(WindowThread,this);

	// wait ready
	WaitReady();
}

//=============================================================================
// stop
//=============================================================================
void Window::Stop(void)
{
	is_loop_ = false;
}

//=============================================================================
// wait
//=============================================================================
void Window::Wait(void)
{
	while(is_loop_);
}

//=============================================================================
// wait ready
//=============================================================================
void Window::WaitReady(void)
{
	while(!is_ready_);
}

//=============================================================================
// window thread
//=============================================================================
void Window::WindowThread(Window* in_window)
{
	// ウィンドウの作成
	in_window->hwnd_ = CreateWindowEx(0,
									  in_window->wndclassex_.lpszClassName,
									  in_window->caption_name_.c_str(),
									  WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZE | WS_MINIMIZEBOX | WS_VISIBLE,
									  CW_USEDEFAULT,
									  CW_USEDEFAULT,
									  in_window->width_ + GetSystemMetrics(SM_CXDLGFRAME) * 2,
									  in_window->height_ + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
									  NULL,
									  NULL,
									  NULL,
									  NULL);

	// ウインドウの表示
	ShowWindow(in_window->hwnd_,SW_SHOW);

	// ウィンドウの更新開始
	UpdateWindow(in_window->hwnd_);

	// is ready
	in_window->is_ready_ = true;

	while(in_window->is_loop_)
	{
		MSG msg;

		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE) == TRUE)
		{
			// PostQuitMessage()が呼ばれたらループ終了
			if(msg.message == WM_QUIT)
			{
				in_window->is_loop_ = false;
			}
			else if(msg.message == WM_DEVICECHANGE)
			{
				GET_DIRECT_INPUT->ResetDevice();
			}
			//else if(msg.message == WM_SIZE)
			//{
				//in_window->is_loop_ = true;
			//}
			else
			{
				// メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		Sleep(static_cast<DWORD>(1000.0f / 60.0f));
	}
}

//-----------------------------------EOF---------------------------------------
