#pragma once
#define PATH_MAX MAX_PATH

#include <Windows.h>
#include <iostream>
#include <string>
#include <direct.h>
#include <atlbase.h>
#include <vector>
#include <codecvt>
#include <locale>
using namespace std;
using convert_t = codecvt_utf8<wchar_t>;
inline wstring_convert<convert_t, wchar_t> strconverter;

// ReSharper disable once CppInconsistentNaming
inline string to_string(wstring wstr) { return strconverter.to_bytes(wstr); }

inline const wchar_t* charToWchar(const char* c) {
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, c, cSize);
	return wc;
}

inline wchar_t* unconstCharToWchar(char* c) {
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, c, cSize);
	return wc;
}