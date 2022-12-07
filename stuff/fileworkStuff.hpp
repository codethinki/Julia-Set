#pragma once
#include <iostream>
#include <windows.h>
#include <sstream>
#include <string>
#include <codecvt>
#include <fstream>
#include <vector>

namespace hlc {
	using namespace std;

	void wreadFile(wstring filepath, vector<wstring>& content);

	inline wstring readFile(string filepath) {
		wifstream file(filepath);
		file.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));
		wstringstream wbuff;
		wbuff << file.rdbuf();
		if (wbuff.str().empty()) throw runtime_error("failed to read file: " + filepath);
		file.close();
		return wbuff.str();
	}

	inline void wreadFile(wstring filepath, vector<wstring>& content) {
		if (filepath.empty()) throw runtime_error("function wreadFile(wstring, vector´<wstring>&): filepath can't be empty");
		wifstream file(filepath);
		file.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));
		wstring line;
		while (getline(file, line)) {
			content.push_back(line);
		}
		file.close();
	}
	inline void readFile(string filepath, vector<string>& content) {
		if (filepath.empty()) throw runtime_error("function readFile(string, vector<string>&): filepath can't be empty");
		ifstream file(filepath);
		file.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));
		string line;
		while (getline(file, line)) {
			content.push_back(line);
		}
		file.close();
	}

	inline wstring wreadFile(wstring filepath, bool throwEmptyError) {
		if (filepath.empty()) throw runtime_error("function wreadFile(wstring, bool): filepath can't be empty");
		wifstream file(filepath);
		file.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));
		wstringstream wbuff;
		wbuff << file.rdbuf();
		if (wbuff.str().empty() && throwEmptyError) throw runtime_error("function wreadFile(wstring, bool): failed to wread file");
		file.close();
		return wbuff.str();
	}
	inline wstring wreadFile(wstring filepath) {
		wstring buff = wreadFile(filepath, true);
		return buff;
	}

	inline int wfindInFile(wstring filepath, wstring string_to_find) {
		wifstream file(filepath);
		wstringstream wbuff;
		wbuff << file.rdbuf();
		int i = 0, start = 0;
		while (wbuff.str().find(string_to_find, start) != wstring::npos && !wbuff.str().empty()) {
			start += string_to_find.size();
			i++;
		}
		file.close();
		return i;
	}
}