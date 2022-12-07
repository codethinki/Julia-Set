#pragma once
#define PATH_MAX MAX_PATH
#define SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include <Windows.h>
#include <iostream>
#include <string>
#include <direct.h>
#include <atlbase.h>
#include <atlconv.h>
#include <codecvt>
#include <TlHelp32.h>

namespace hlc {
	inline std::string getClipboardText() {
		using namespace std;
		if (!OpenClipboard(nullptr)) {
			throw runtime_error("function getClipboardText: can't open clipboard");
		}
		const HANDLE hData = GetClipboardData(CF_TEXT);
		const char* pszText = static_cast<char*>(GlobalLock(hData));
		if (pszText == nullptr) throw runtime_error("function getClipboardText: cb text = null");
		string text = pszText;
		GlobalUnlock(hData);
		CloseClipboard();
		return text;
	}

	inline int hiddenCmd(std::string command, std::string path) {
		//don't use "" around the path :)
		using namespace std;
		PROCESS_INFORMATION pInfo;
		STARTUPINFO sInfo;
		DWORD returnValue;
		string cmd = "cmd.exe /c ";
		cmd += command;
		CA2T commandline(cmd.c_str());
		memset(&sInfo, 0, sizeof(sInfo));
		memset(&pInfo, 0, sizeof(pInfo));
		sInfo.cb = sizeof(sInfo);
		bool process = false;
		if (!path.empty()) {
			CA2T location(path.c_str());
			process = CreateProcessW(NULL, commandline, NULL, NULL, FALSE,
									 NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW,
									 NULL, location, &sInfo, &pInfo);
		} else {
			process = CreateProcessW(nullptr, commandline, nullptr, nullptr, FALSE,
									 NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW,
									 nullptr, nullptr, &sInfo, &pInfo);
		}
		if (process) {
			WaitForSingleObject(pInfo.hProcess, INFINITE);
			GetExitCodeProcess(pInfo.hProcess, &returnValue);
			CloseHandle(pInfo.hProcess);
			CloseHandle(pInfo.hThread);
		} else {
			cout << endl << "Command failed" << endl;
			throw runtime_error("hidden cmd: command not working");
			return -1;
		}
		return returnValue;
	}

	inline void processActive(const std::wstring& process_name, int& process_count) {
		using namespace std;
		PROCESSENTRY32 proc;
		proc.dwSize = sizeof(PROCESSENTRY32);
		const HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		Process32First(snapshot, &proc);
		do {
			if (process_name == proc.szExeFile)
				process_count += 1;
		} while (TRUE == Process32Next(snapshot, &proc));
	}

	inline void getDesktopResolution(int& horizontal, int& vertical) {
		RECT desktop;
		const HWND hDesktop = GetDesktopWindow();
		GetWindowRect(hDesktop, &desktop);
		horizontal = desktop.right;
		vertical = desktop.bottom;
	}

	inline int messageBox(const std::wstring& box_title, const std::wstring& box_text, UINT box_args) {
		using namespace std;
		int msgboxID = MessageBox(
			NULL,
			box_text.c_str(),
			box_title.c_str(),
			box_args
		);
		return msgboxID;
	}
}