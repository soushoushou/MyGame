#pragma once
#include <string>
#define _T(x)      L ## x

using namespace std;
void WStrToUTF8(string& dest, const wstring& src);
string WStrToUTF8(const wstring& str);