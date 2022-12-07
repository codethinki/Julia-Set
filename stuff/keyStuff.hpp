#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
#include <fstream>
#include <string>
#include <codecvt>
#include <chrono>

using namespace std;
using namespace chrono;

void keyDown(int keyCode) {
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wVk = keyCode;
	ip.ki.dwFlags = 0;
	SendInput(1, &ip, sizeof(INPUT));
}
void keyUp(int keyCode) {
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wVk = keyCode;
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}
void pressKey(int keyCode) {
	INPUT ip[2];
	ip[0].type, ip[1].type = INPUT_KEYBOARD;
	ip[0].ki.wVk, ip[1].ki.wVk = keyCode;
	ip[0].ki.dwFlags = 0, ip[1].ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(2, ip, sizeof(INPUT));
}
void pressShiftKey(int keyCode) {
	keyDown(VK_SHIFT);
	pressKey(keyCode);
	keyUp(VK_SHIFT);
}
void pressControlKey(int keyCode) {
	keyDown(VK_CONTROL);
	pressKey(keyCode);
	keyUp(VK_CONTROL);
}
void pressControlAltKey(int keyCode) {
	keyDown(VK_CONTROL);
	keyDown(VK_MENU);
	pressKey(keyCode);
	keyUp(VK_MENU);
	keyUp(VK_CONTROL);
}

boolean pressSpecialKey(string key) {
	if(key == "F1") {
		pressKey(0x70);
	} else if(key == "F2") {
		pressKey(0x71);
	} else if(key == "F3") {
		pressKey(0x72);
	} else if(key == "F4") {
		pressKey(0x73);
	} else if(key == "F5") {
		pressKey(0x74);
	} else if(key == "F6") {
		pressKey(0x75);
	} else if(key == "F7") {
		pressKey(0x76);
	} else if(key == "F8") {
		pressKey(0x77);
	} else if(key == "F9") {
		pressKey(0x78);
	} else if(key == "F10") {
		pressKey(0x79);
	} else if(key == "F11") {
		pressKey(0x7A);
	} else if(key == "F12") {
		pressKey(0x7B);
	} else if(key == "DOWN") {
		pressKey(VK_DOWN);
	} else if(key == "UP") {
		pressKey(VK_UP);
	} else if(key == "RIGHT") {
		pressKey(VK_RIGHT);
	} else if(key == "LEFT") {
		pressKey(VK_LEFT);
	} else {
		string errorMessage("Cant resolve: " + key);
		throw runtime_error(errorMessage);
	}
	return true;
}


void keyDownCmd(int keyCode, vector<INPUT>& vec) {
	INPUT input;
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = keyCode;
	input.ki.dwFlags = 0;
	vec.push_back(input);
}
void keyUpCmd(int keyCode, vector<INPUT>& vec) {
	INPUT input;
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = keyCode;
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	vec.push_back(input);
}
void pressKeyCmd(int keyCode, vector<INPUT>& vec) {
	keyDownCmd(keyCode, vec);
	keyUpCmd(keyCode, vec);
}
void pressShiftKeyCmd(int keyCode, vector<INPUT>& vec) {
	keyDownCmd(VK_SHIFT, vec);
	pressKeyCmd(keyCode, vec);
	keyUpCmd(VK_SHIFT, vec);
}
void pressControlKeyCmd(int keyCode, vector<INPUT>& vec) {
	keyDownCmd(VK_CONTROL, vec);
	pressKeyCmd(keyCode, vec);
	keyUpCmd(VK_CONTROL, vec);
}
void pressControlAltKeyCmd(int keyCode, vector<INPUT>& vec) {
	keyDownCmd(VK_MENU, vec);
	pressControlKeyCmd(keyCode, vec);
	keyUpCmd(VK_MENU, vec);
}
void pressSpecialAltKeyCmd(int keyCode, vector<INPUT>& vec) {
	keyDownCmd(VK_MENU, vec);
	string buff = to_string(keyCode);
	for(int i = 0; i < buff.size(); i++) {
		switch(buff[i]) {
			case '0':
				pressKeyCmd(VK_NUMPAD0, vec);
				break;
			case '1':
				pressKeyCmd(VK_NUMPAD1, vec);
				break;
			case '2':
				pressKeyCmd(VK_NUMPAD2, vec);
				break;
			case '3':
				pressKeyCmd(VK_NUMPAD3, vec);
				break;
			case '4':
				pressKeyCmd(VK_NUMPAD4, vec);
				break;
			case '5':
				pressKeyCmd(VK_NUMPAD5, vec);
				break;
			case '6':
				pressKeyCmd(VK_NUMPAD6, vec);
				break;
			case '7':
				pressKeyCmd(VK_NUMPAD7, vec);
				break;
			case '8':
				pressKeyCmd(VK_NUMPAD8, vec);
				break;
			case '9':
				pressKeyCmd(VK_NUMPAD9, vec);
				break;
			default:
				throw runtime_error("function pressSpecialAltKey invalid keyCode" + buff + " :: " + buff[i]);
				break;
		}
	}
	keyUpCmd(VK_MENU, vec);
}

vector<INPUT> getTypeCmdList(wstring str) {
	vector<INPUT> inputs;
	for(int i = 0; i < str.size(); i++) {
		uint32_t c = str[i];
		switch(c) {
			case L'a':
				pressKeyCmd(0x41, inputs);
				break;
			case L'A':
				pressShiftKeyCmd(0x41, inputs);
				break;
			case L'b':
				pressKeyCmd(0x42, inputs);
				break;
			case L'B':
				pressShiftKeyCmd(0x42, inputs);
				break;
			case L'c':
				pressKeyCmd(0x43, inputs);
				break;
			case L'C':
				pressShiftKeyCmd(0x43, inputs);
				break;
			case L'd':
				pressKeyCmd(0x44, inputs);
				break;
			case L'D':
				pressShiftKeyCmd(0x44, inputs);
				break;
			case L'e':
				pressKeyCmd(0x45, inputs);
				break;
			case L'E':
				pressShiftKeyCmd(0x45, inputs);
				break;
			case L'\u20ac':
				pressControlAltKeyCmd(0x45, inputs);
				break;
			case L'f':
				pressKeyCmd(0x46, inputs);
				break;
			case L'F':
				pressShiftKeyCmd(0x46, inputs);
				break;
			case L'g':
				pressKeyCmd(0x47, inputs);
				break;
			case L'G':
				pressShiftKeyCmd(0x47, inputs);
				break;
			case L'h':
				pressKeyCmd(0x48, inputs);
				break;
			case L'H':
				pressShiftKeyCmd(0x48, inputs);
				break;
			case L'i':
				pressKeyCmd(0x49, inputs);
				break;
			case L'I':
				pressShiftKeyCmd(0x49, inputs);
				break;
			case L'j':
				pressKeyCmd(0x4A, inputs);
				break;
			case L'J':
				pressShiftKeyCmd(0x4A, inputs);
				break;
			case L'k':
				pressKeyCmd(0x4B, inputs);
				break;
			case L'K':
				pressShiftKeyCmd(0x4B, inputs);
				break;
			case L'l':
				pressKeyCmd(0x4C, inputs);
				break;
			case L'L':
				pressShiftKeyCmd(0x4C, inputs);
				break;
			case L'm':
				pressKeyCmd(0x4D, inputs);
				break;
			case L'M':
				pressShiftKeyCmd(0x4D, inputs);
				break;
			case L'\u00b5':
				pressControlAltKeyCmd(0x4D, inputs);
				break;
			case L'n':
				pressKeyCmd(0x4E, inputs);
				break;
			case L'N':
				pressShiftKeyCmd(0x4E, inputs);
				break;
			case L'o':
				pressKeyCmd(0x4F, inputs);
				break;
			case L'O':
				pressShiftKeyCmd(0x4F, inputs);
				break;
			case L'p':
				pressKeyCmd(0x50, inputs);
				break;
			case L'P':
				pressShiftKeyCmd(0x50, inputs);
				break;
			case L'q':
				pressKeyCmd(0x51, inputs);
				break;
			case L'Q':
				pressShiftKeyCmd(0x51, inputs);
				break;
			case L'\u0040':
				pressControlAltKeyCmd(0x51, inputs);
				break;
			case L'r':
				pressKeyCmd(0x52, inputs);
				break;
			case L'R':
				pressShiftKeyCmd(0x52, inputs);
				break;
			case L's':
				pressKeyCmd(0x53, inputs);
				break;
			case L'S':
				pressShiftKeyCmd(0x53, inputs);
				break;
			case L't':
				pressKeyCmd(0x54, inputs);
				break;
			case L'T':
				pressShiftKeyCmd(0x54, inputs);
				break;
			case L'u':
				pressKeyCmd(0x55, inputs);
				break;
			case L'U':
				pressShiftKeyCmd(0x55, inputs);
				break;
			case L'v':
				pressKeyCmd(0x56, inputs);
				break;
			case L'V':
				pressShiftKeyCmd(0x56, inputs);
				break;
			case L'w':
				pressKeyCmd(0x57, inputs);
				break;
			case L'W':
				pressShiftKeyCmd(0x57, inputs);
				break;
			case L'x':
				pressKeyCmd(0x58, inputs);
				break;
			case L'X':
				pressShiftKeyCmd(0x58, inputs);
				break;
			case L'y':
				pressKeyCmd(0x59, inputs);
				break;
			case L'Y':
				pressShiftKeyCmd(0x59, inputs);
				break;
			case L'z':
				pressKeyCmd(0x5A, inputs);
				break;
			case L'Z':
				pressShiftKeyCmd(0x5A, inputs);
				break;
			case L'ü':
				pressKeyCmd(VK_OEM_1, inputs);
				break;
			case L'Ü':
				pressShiftKeyCmd(VK_OEM_1, inputs);
				break;
			case L'ö':
				pressKeyCmd(VK_OEM_3, inputs);
				break;
			case L'Ö':
				pressShiftKeyCmd(VK_OEM_3, inputs);
				break;
			case L'ä':
				pressKeyCmd(VK_OEM_7, inputs);
				break;
			case L'Ä':
				pressShiftKeyCmd(VK_OEM_7, inputs);
				break;
			case L'1':
				pressKeyCmd(0x31, inputs);
				break;
			case L'!':
				pressShiftKeyCmd(0x31, inputs);
				break;
			case L'2':
				pressKeyCmd(0x32, inputs);
				break;
			case L'\u0022':
				pressShiftKeyCmd(0x32, inputs);
				break;
			case L'\u00b2':
				pressControlAltKeyCmd(0x32, inputs);
				break;
			case L'3':
				pressKeyCmd(0x33, inputs);
				break;
			case L'§':
				pressShiftKeyCmd(0x33, inputs);
				break;
			case L'\u00b3':
				pressControlAltKeyCmd(0x33, inputs);
				break;
			case L'4':
				pressKeyCmd(0x34, inputs);
				break;
			case L'$':
				pressShiftKeyCmd(0x34, inputs);
				break;
			case L'5':
				pressKeyCmd(0x35, inputs);
				break;
			case L'%':
				pressShiftKeyCmd(0x35, inputs);
				break;
			case L'6':
				pressKeyCmd(0x36, inputs);
				break;
			case L'&':
				pressShiftKeyCmd(0x36, inputs);
				break;
			case L'7':
				pressKeyCmd(0x37, inputs);
				break;
			case L'/':
				pressShiftKeyCmd(0x37, inputs);
				break;
			case L'\u007b':
				pressControlAltKeyCmd(0x37, inputs);
				break;
			case L'8':
				pressKeyCmd(0x38, inputs);
				break;
			case L'(':
				pressShiftKeyCmd(0x38, inputs);
				break;
			case L'\u005b':
				pressControlAltKeyCmd(0x38, inputs);
				break;
			case L'9':
				pressKeyCmd(0x39, inputs);
				break;
			case L')':
				pressShiftKeyCmd(0x39, inputs);
				break;
			case L'\u005d':
				pressControlAltKeyCmd(0x39, inputs);
				break;
			case L'0':
				pressKeyCmd(0x30, inputs);
				break;
			case L'=':
				pressShiftKeyCmd(0x30, inputs);
				break;
			case L'\u007d':
				pressControlAltKeyCmd(0x30, inputs);
				break;
			case L'ß':
				pressKeyCmd(VK_OEM_4, inputs);
				break;
			case L'?':
				pressShiftKeyCmd(VK_OEM_4, inputs);
				break;
			case L'\u005c':
				pressControlAltKeyCmd(VK_OEM_4, inputs);
				break;
			case L'´':
				pressKeyCmd(VK_OEM_6, inputs);
				break;
			case L'`':
				pressShiftKeyCmd(VK_OEM_6, inputs);
				break;
			case L'^':
				pressKeyCmd(VK_OEM_5, inputs);
				break;
			case L'°':
				pressShiftKeyCmd(VK_OEM_5, inputs);
				break;
			case L'<':
				pressKeyCmd(VK_OEM_102, inputs);
				break;
			case L'>':
				pressShiftKeyCmd(VK_OEM_102, inputs);
				break;
			case L'|':
				pressControlAltKeyCmd(VK_OEM_102, inputs);
				break;
			case L'\u0020':
				pressKeyCmd(VK_SPACE, inputs);
				break;
			case L',':
				pressKeyCmd(VK_OEM_COMMA, inputs);
				break;
			case L';':
				pressShiftKeyCmd(VK_OEM_COMMA, inputs);
				break;
			case L'.':
				pressKeyCmd(VK_OEM_PERIOD, inputs);
				break;
			case L':':
				pressShiftKeyCmd(VK_OEM_PERIOD, inputs);
				break;
			case L'-':
				pressKeyCmd(VK_OEM_MINUS, inputs);
				break;
			case L'_':
				pressShiftKeyCmd(VK_OEM_MINUS, inputs);
				break;
			case L'#':
				pressKeyCmd(VK_OEM_2, inputs);
				break;
			case L'\u0027':
				pressShiftKeyCmd(VK_OEM_2, inputs);
				break;
			case L'+':
				pressKeyCmd(VK_OEM_PLUS, inputs);
				break;
			case L'*':
				pressShiftKeyCmd(VK_OEM_PLUS, inputs);
				break;
			case L'~':
				pressControlAltKeyCmd(VK_OEM_PLUS, inputs);
				break;
			case L'\u000d':
				//ENTER
				pressKeyCmd(VK_RETURN, inputs);
				break;
			case L'\n':
				//ENTER
				pressKeyCmd(VK_RETURN, inputs);
				break;
			case L'’':
				pressSpecialAltKeyCmd((int) L'’', inputs);
				break;
			case L'—':
				pressSpecialAltKeyCmd((int) L'’', inputs);
				break;
			case L'•':
				pressSpecialAltKeyCmd((int) L'•', inputs);
				break;
			case L'“':
				pressSpecialAltKeyCmd((int) L'“', inputs);
				break;
			default:
				wstring fatalSymbol;
				fatalSymbol = c;
				throw runtime_error("can't type this: " + str[i]);
		}
	}
	return inputs;
}

inline bool vecSendInput(vector<INPUT> vec) {
	//array<INPUT, static_cast<size_t>(vec.size())> hello;

	if(const UINT send = SendInput(vec.size(), vec.data(), sizeof(INPUT) ); send != vec.size()) return false;
	return true;
}

bool sendInputTimed(vector<INPUT> vec, const uint32_t keys_per_package, const uint32_t wait_ms) {
	if(keys_per_package == 0) throw runtime_error("function SendInputTimed: keysPerPackage can't be 0");
	for(int i = keys_per_package; i < vec.size(); i += keys_per_package) {
		const vector<INPUT> package = { vec.begin() + i - keys_per_package, vec.begin() + i };
		vecSendInput(package);
		time_point end = high_resolution_clock::now() + milliseconds(wait_ms);
		while(high_resolution_clock::now() < end) {}
	}
	if(vec.size() % keys_per_package != 0) {
		const vector<INPUT> package = { vec.end() - vec.size() % keys_per_package, vec.end() };
		vecSendInput(package);
	}
	return true;
}
