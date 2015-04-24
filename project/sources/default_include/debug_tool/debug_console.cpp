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

	// �R���\�[���̍쐬
	AllocConsole();

	// �R���\�[���E�B���h�E�̃^�C�g��
	SetConsoleTitle(CAPTION);

	// �R���\�[���E�B���h�E�n���h���̎擾
	hwnd_ = GetConsoleWindow();

	// �o�b�t�@�T�C�Y�̐ݒ�
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),coord);

	// �E�B���h�E�T�C�Y�̐ݒ�
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE),TRUE,&small_rect);

	// �������ݗp�t�@�C���p�X
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
// �\��
//=============================================================================
void DebugConsole::Show(void)
{
#ifndef _RELEASE
	ShowWindow(hwnd_,SW_SHOW);
	is_show_ = true;
#endif
}

//=============================================================================
// ��\��
//=============================================================================
void DebugConsole::Hide(void)
{
#ifndef _RELEASE
	ShowWindow(hwnd_,SW_HIDE);
	is_show_ = false;
#endif
}

//=============================================================================
// �\���؂芷��
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

	// �ψ����̎Q�ƊJ�n
	va_start(args,format);

	// ������ɕύX
	vsprintf(work,format,args);

	// �ψ����̎Q�ƏI��
	va_end(args);

	// ���O�ɏ���
	strcat(string_,work);
#endif
}

//-----------------------------------EOF---------------------------------------
