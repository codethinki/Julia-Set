#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <future>
#include "MyApp.hpp"
#include <stuff/windowsStuff.hpp>
#include <stuff/fileworkStuff.hpp>
using namespace std;
using namespace hlc;

int compileShaders() {
	wstring frag32 = wreadFile(L"shaders/shader.frag", false);
	while(frag32.find(L"double") != wstring::npos) frag32.replace(frag32.find(L"double"), 6, L"float");
	wofstream file("shaders/shader32.frag");
	file.write(frag32.c_str(), frag32.size());
	file.close();

	const future<int> result = async(hiddenCmd, "call \"Vert_Frag_Compiler.bat\"", R"(E:\Visual Studio\repos\Julia_Set\Julia_Set\shaders)");
	result.wait();
	wstring vert = wreadFile(L"shaders/vert.txt", false);
	wstring frag = wreadFile(L"shaders/frag.txt", false);
	frag32 = wreadFile(L"shaders/frag32.txt", false);
	if (!vert.empty() || !frag.empty() || !frag32.empty()) {
		if (!vert.empty()) {
			wcout << L"Vertex shader error in line " << vert.substr(vert.find(L':') + 1, vert.find(L':', vert.find(L':') + 1) - vert.find(L':')) << endl;
			wcout << vert.replace(0, vert.find(L"error:"), L"") << endl;
		}
		if (!frag.empty()) {
			wcout << L"Fragment shader error in line " << frag.substr(frag.find(L':') + 1, frag.find(L':', frag.find(L':') + 1) - frag.find(L':')) << endl;
			wcout << frag.replace(0, frag.find(L"error:"), L"") << endl;
		}
		if (!frag32.empty()) {
			wcout << L"Fragment shader32 error in line " << frag32.substr(frag32.find(L':') + 1, frag32.find(L':', frag32.find(L':') + 1) - frag32.find(L':')) << endl;
			wcout << frag32.replace(0, frag32.find(L"error:"), L"") << endl;
		}
		exit(EXIT_FAILURE);
		return 1;
	}
	return 0;
}
#ifdef DEBUG
int main() {
#else
INT WINAPI WinMain(HINSTANCE h_instance, HINSTANCE h_prev_instance, char* lp_cmd_line, int n_cmd_show) {
#endif
#ifdef DEBUG
	compileShaders();
#endif
	MyApp app{};
	try {
		app.run();
	} catch (const exception& e) {
		cerr << e.what() << endl;
#ifdef DEBUG

		throw runtime_error("stop");
		return EXIT_FAILURE;
#else
		Sleep(20);
		return EXIT_FAILURE;
#endif
	}
	return EXIT_SUCCESS;
}

