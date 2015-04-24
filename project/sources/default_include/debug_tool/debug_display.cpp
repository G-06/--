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
// 更新
//=============================================================================
void DebugDisplay::Update(void)
{
#ifndef _RELEASE
#endif // _RELEASE
}

//=============================================================================
// 描画
//=============================================================================
void DebugDisplay::Draw(void)
{
#ifndef _RELEASE
	if(is_show_)
	{
		RECT rect = {0,0,GET_SYSTEM.__window()->__width(),GET_SYSTEM.__window()->__height()};

		// テキスト描画
		font_->DrawText(NULL,string_,-1,&rect,DT_LEFT,D3DXCOLOR(0.0f,0.0f,0.0f,1.0f));

		// デバッグ情報のクリア
		memset(string_,'\0',sizeof(s8) * STRING_MAX);
	}

	ZeroMemory(string_,sizeof(s8) * STRING_MAX);

#endif // _RELEASE
}

//=============================================================================
// 終了
//=============================================================================
void DebugDisplay::Uninitialize(void)
{
#ifndef _RELEASE
#endif // _RELEASE
}

//=============================================================================
// 出力
//=============================================================================
void DebugDisplay::Print(const char* format,...)
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
#endif // _RELEASE
}

//-----------------------------------EOF---------------------------------------
