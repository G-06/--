//*****************************************************************************
//
// assert
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "assert.h"
#include "system/system.h"

#ifndef _RELEASE

//=============================================================================
// assert
//=============================================================================
void Assert(bool in_expression,const s8* in_filename,u32 in_line,const s8* in_message)
{
	if(in_expression)
	{
		s8 message[_MAX_FNAME + _MAX_EXT + 256];

		sprintf(message,"file : %s\nline : %d\n%s",in_filename,in_line,in_message);
		MessageBox(GET_SYSTEM.__window()->__hwnd(),message,"error",MB_ICONEXCLAMATION);
	}
}

#endif // _RELEASE
//-----------------------------------EOF---------------------------------------
