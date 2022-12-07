#pragma once
#include <iostream>
#include <urlmon.h>
#include <Windows.h>
#include <string>
using namespace std;
//requires urlmon.lib
inline HRESULT downloadHTML(wstring url) {
	const HRESULT result = URLDownloadToFile(nullptr, url.c_str(), L"result.html", 0, nullptr);
	if (result != S_OK) throw runtime_error("function getHTMLFile: couldn't download file");
	return result;
}
