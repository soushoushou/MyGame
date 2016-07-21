#pragma once
#include <string>
using namespace std;
void WStrToUTF8(string& dest, const wstring& src);
string WStrToUTF8(const wstring& str);