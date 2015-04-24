//*****************************************************************************
//
// debug display
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "debug_display.h"
#include "system/system.h"

//=============================================================================
// constructor
//=============================================================================
DebugDisplay::DebugDisplay(void):
is_show_(false)
{
#ifndef _RELEASE
	is_show_ = true;
#endif // _RELEASE
}

//=============================================================================
// destructor
//=============================================================================
DebugDisplay::~DebugDisplay(void)
{
#ifndef _RELEASE
#endif // _RELEASE
}

//=============================================================================
// initializer
//=============================================================================
bool DebugDisplay::Initialize(void)
{
#ifndef _RELEASE
	ZeroMemory(string_,sizeof(s8) * STRING_MAX);

	D3DXCreateFont(GET_DIRECTX9_DEVICE,32,12,0,0,FALSE,SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"Terminal",&font_);
#endif // _RELEASE
	return true;
}

//=============================================================================
// �X�V
//=============================================================================
void DebugDisplay::Update(void)
{
#ifndef _RELEASE
#endif // _RELEASE
}

//=============================================================================
// �`��
//=============================================================================
void DebugDisplay::Draw(void)
{
#ifndef _RELEASE
	if(is_show_)
	{
		RECT rect = {0,0,GET_SYSTEM.__window()->__width(),GET_SYSTEM.__window()->__height()};

		// �e�L�X�g�`��
		font_->DrawText(NULL,string_,-1,&rect,DT_LEFT,D3DXCOLOR(0.0f,0.0f,0.0f,1.0f));

		// �f�o�b�O���̃N���A
		memset(string_,'\0',sizeof(s8) * STRING_MAX);
	}

	ZeroMemory(string_,sizeof(s8) * STRING_MAX);

#endif // _RELEASE
}

//=============================================================================
// �I��
//=============================================================================
void DebugDisplay::Uninitialize(void)
{
#ifndef _RELEASE
#endif // _RELEASE
}

//=============================================================================
// �o��
//=============================================================================
void DebugDisplay::Print(const char* format,...)
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
#endif // _RELEASE
}

//-----------------------------------EOF---------------------------------------
