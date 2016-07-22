#include "toolFunctions.h"

bool WideStringToString(const std::wstring& src, std::string &str)
{
	std::locale sys_locale("");

	const wchar_t* data_from = src.c_str();
	const wchar_t* data_from_end = src.c_str() + src.size();
	const wchar_t* data_from_next = 0;

	int wchar_size = 4;
	char* data_to = new char[(src.size() + 1) * wchar_size];
	char* data_to_end = data_to + (src.size() + 1) * wchar_size;
	char* data_to_next = 0;

	memset(data_to, 0, (src.size() + 1) * wchar_size);

	typedef std::codecvt<wchar_t, char, mbstate_t> convert_facet;
	mbstate_t out_state = { 0 };
	auto result = std::use_facet<convert_facet>(sys_locale).out(
		out_state, data_from, data_from_end, data_from_next,
		data_to, data_to_end, data_to_next);
	if (result == convert_facet::ok)
	{
		str = data_to;
		delete[] data_to;
		return true;
	}
	delete[] data_to;
	return false;
}

bool StringToWideString(const std::string& src, std::wstring &wstr)
{
	std::locale sys_locale("");
	const char* data_from = src.c_str();
	const char* data_from_end = src.c_str() + src.size();
	const char* data_from_next = 0;

	wchar_t* data_to = new wchar_t[src.size() + 1];
	wchar_t* data_to_end = data_to + src.size() + 1;
	wchar_t* data_to_next = 0;

	wmemset(data_to, 0, src.size() + 1);

	typedef std::codecvt<wchar_t, char, mbstate_t> convert_facet;
	mbstate_t in_state = { 0 };
	auto result = std::use_facet<convert_facet>(sys_locale).in(
		in_state, data_from, data_from_end, data_from_next,
		data_to, data_to_end, data_to_next);
	if (result == convert_facet::ok)
	{
		wstr = data_to;
		delete[] data_to;
		return true;
	}
	delete[] data_to;
	return false;
}


bool WCharStringToUTF8String(const std::wstring &wstr, std::string &u8str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	u8str = conv.to_bytes(wstr);
	return true;
}

bool UTF8StringToWCharString(const std::string &u8str, std::wstring &wstr)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
	wstr = conv.from_bytes(u8str);
	return true;
}




//utf-8转unicode
std::wstring Utf82Unicode(const std::string& utf8string)
{
	int widesize = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, NULL, 0);
	if (widesize == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid UTF-8 sequence.");
	}
	if (widesize == 0)
	{
		throw std::exception("Error in conversion.");
	}

	std::vector<wchar_t> resultstring(widesize);

	int convresult = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, &resultstring[0], widesize);

	if (convresult != widesize)
	{
		throw std::exception("La falla!");
	}

	return std::wstring(&resultstring[0]);
}


//unicode 转为 ascii  
std::string WideByte2Acsi(std::wstring& wstrcode)
{
	int asciisize = ::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, NULL, 0, NULL, NULL);
	if (asciisize == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid UTF-8 sequence.");
	}
	if (asciisize == 0)
	{
		throw std::exception("Error in conversion.");
	}
	std::vector<char> resultstring(asciisize);
	int convresult = ::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, &resultstring[0], asciisize, NULL, NULL);

	if (convresult != asciisize)
	{
		throw std::exception("La falla!");
	}

	return std::string(&resultstring[0]);
}



//utf-8 转 ascii  
std::string UTF_82ASCII(std::string& strUtf8Code)
{
	std::string strRet("");
	//先把 utf8 转为 unicode  
	std::wstring wstr = Utf82Unicode(strUtf8Code);
	//最后把 unicode 转为 ascii  
	strRet = WideByte2Acsi(wstr);
	return strRet;
}



//ascii 转 Unicode  
std::wstring Acsi2WideByte(std::string& strascii)
{
	int widesize = MultiByteToWideChar(CP_ACP, 0, (char*)strascii.c_str(), -1, NULL, 0);
	if (widesize == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid UTF-8 sequence.");
	}
	if (widesize == 0)
	{
		throw std::exception("Error in conversion.");
	}
	std::vector<wchar_t> resultstring(widesize);
	int convresult = MultiByteToWideChar(CP_ACP, 0, (char*)strascii.c_str(), -1, &resultstring[0], widesize);
	if (convresult != widesize)
	{
		throw std::exception("La falla!");
	}
	return std::wstring(&resultstring[0]);
}


//Unicode 转 Utf8  
std::string Unicode2Utf8(const std::wstring& widestring)
{
	int utf8size = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, NULL, 0, NULL, NULL);
	if (utf8size == 0)
	{
		throw std::exception("Error in conversion.");
	}
	std::vector<char> resultstring(utf8size);
	int convresult = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, &resultstring[0], utf8size, NULL, NULL);
	if (convresult != utf8size)
	{
		throw std::exception("La falla!");
	}
	return std::string(&resultstring[0]);
}


//ascii 转 Utf8  
string ASCII2UTF_8(string strAsciiCode)
{
//	string strRet("");
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//	#if defined(_MSC_VER)
//		//先把 ascii 转为 unicode  
//		std::wstring wstr = Acsi2WideByte(strAsciiCode);
//		//最后把 unicode 转为 utf8  
//		strRet = Unicode2Utf8(wstr);
//	#else
//		strRet = strAsciiCode;
//	#endif
//#else
//	strRet = strAsciiCode;
//#endif
//	return strRet;
	wstring tmp;
	string result;
	if (!StringToWideString(strAsciiCode, tmp))
		return strAsciiCode;
	if (!WCharStringToUTF8String(tmp, result))
		return strAsciiCode;
	return result;
}



