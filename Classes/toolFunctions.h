#pragma once
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif // _WIN32
#include <vector>
using namespace std;
#define _T(x)      L ## x

string ASCII2UTF_8(string strAsciiCode);		//win32ÏÂANSI×ªutf-8