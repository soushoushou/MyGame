#pragma once
#include <string>
#include <tchar.h>
using namespace std;
void WStrToUTF8(string& dest, const wstring& src);
string WStrToUTF8(const wstring& str);