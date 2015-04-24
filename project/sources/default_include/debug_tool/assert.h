//*****************************************************************************
//
// assert
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include gaurd
//*****************************************************************************
#pragma once
#ifndef _ASSERT_H_
#define _ASSERT_H_

//*****************************************************************************
// macro definition
//*****************************************************************************
#ifndef _RELEASE
void Assert(bool in_expression,const s8* in_filename,u32 in_line,const s8* in_message);

#define ASSERT_EXP(expression,message) \
{\
	Assert((expression),__FILE__,__LINE__,message);\
}

#define ASSERT(message) ASSERT_EXP(true,message)
#else
#define ASSERT_EXP(expression,message)
#define ASSERT(message)
#endif // _RELEASE

#endif // _ASSERT_H_

//---------------------------------- EOF --------------------------------------
