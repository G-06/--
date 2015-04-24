//*****************************************************************************
//
// プリコンパイル済みヘッダー
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include gaurd
//*****************************************************************************
#pragma once

#ifndef _STDAFX_H_
#define _STDAFX_H_

//*****************************************************************************
// stl
//*****************************************************************************
#include <map>
#include <list>
#include <vector>
#include <string>
#include <algorithm>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <process.h>
#include <io.h>
#include <fcntl.h>
#pragma comment (lib,"winmm.lib")

#include <d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")

#include <xaudio2.h>

#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#pragma comment (lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

#endif // _STDAFX_H_

//-----------------------------------EOF---------------------------------------