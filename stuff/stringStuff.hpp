#pragma once
#include <iostream>
#include <vector>
namespace hlc {
	inline bool isNum(std::wstring wstring) {
		for (wchar_t i : wstring) if (!isdigit(i) && i != L'.') return false;
		return true;
	}

	inline bool isNum(std::string string) {
		for (char i : string) if (!isdigit(i) && i != '.') return false;
		return true;
	}

	inline void coutWString(const std::wstring& string) {
		using namespace std;
		wcout.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));
		wcout << string << endl;
	}

	inline std::vector<std::wstring> wsplit(std::wstring content, const wchar_t* split) {
		std::wstring splitSymbol = split;
		std::vector<std::wstring> tokens;
		while (content.find(split) != -1) {
			tokens.push_back(content.substr(0, content.find(split)));
			content.replace(0, tokens[tokens.size() - 1].size() + splitSymbol.length(), L"");
		}
		tokens.push_back(content);
		return tokens;
	}
	inline void toNumber(wstring& string) {
		bool deciPoint = false, opr = false;
		std::wstring buff;
		for (int i = 0; i < string.size(); i++) if (isdigit(string[i]) || (string[i] == '.' && !deciPoint) || ((string[i] == '+' || string[i] == '-') && !opr)) {
			if(string[i] == '+' || string[i] == '-') opr = false;
			if(string[i] == '.') deciPoint = true;
			buff += string[i];
		}
		string = buff;
	}
}