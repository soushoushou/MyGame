#pragma once
#include <string>
#include "platform/CCPlatformMacros.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <windows.h>
#endif // _WIN32
#include <vector>
using namespace std;
#define _T(x)      L ## x

string ASCII2UTF_8(string strAsciiCode);		//win32ÏÂANSI×ªutf-8