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
const u32 MainWindow::DEFAULT_WIDTH		= DEFAULT_SCREEN_WIDTH;		// ����
const u32 MainWindow::DEFAULT_HEIGHT	= DEFAULT_SCREEN_HEIGHT;	// �c��
const s8* MainWindow::CLASS_NAME		= "MainWindow";				// �N���X��
const s8* MainWindow::CAPTION_NAME		= "framework";				// �L���v�V������

//=============================================================================
// constructor
//=============================================================================
MainWindow::MainWindow(HINSTANCE in_hinstance)
{
	WNDCLASSEX wndclassex =
	{
		sizeof(WNDCLASSEX),				// �\���̂̃T�C�Y
		CS_CLASSDC,						// �X�^�C��
		WindowProcedure,				// �v���V�[�W���̊֐��|�C���^
		0,								// 
		0,								// 
		in_hinstance,					// �C���X�^���X
		NULL,							// �A�C�R��
		LoadCursor(NULL, IDC_ARROW),	// �}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),		// �w�i�F
		NULL,							// ���j���[
		CLASS_NAME,						// �E�B���h�E�̃N���X��
		NULL							// �A�C�R��
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
	case WM_DESTROY:			// �E�B���h�E��j��
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:			// �L�[����
		switch(in_wparam)
		{
		case VK_ESCAPE:			// �G�X�P�[�v�L�[
			// �E�B���h�E�̔j��
			DestroyWindow(in_hwnd);
			break;
		case VK_INSERT:			// �C���T�[�g�L�[
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
