#pragma once

#include  "HlcDevice.hpp"
#include "HlcModel.hpp"
#include "HlcGameObject.hpp"
#include "HlcWindow.hpp"
#include "HlcRenderer.hpp"

#include <vector>
namespace hlc {

	using namespace std;
	class MyApp {
	public:
		bool wideShader = true;
		static constexpr int WIDTH = 1000;
		static constexpr int HEIGHT = 1000;
		inline static const string VERT_SHADER_PATH = "shaders/vert.spv";
		inline static const string FRAG_SHADER_PATH = "shaders/frag.spv";
		inline static const string FRAG_SHADER32_PATH = "shaders/frag32.spv";
		inline static const string WINDOW_NAME = "Julia Set";
		MyApp();
		~MyApp();

		MyApp(const MyApp&) = delete;
		MyApp& operator=(const MyApp&) = delete;
		void run();
	private:

		HlcWindow hlcWindow{ WIDTH, HEIGHT, WINDOW_NAME };
		HlcDevice hlcDevice{ hlcWindow };
		HlcRenderer hlcRenderer{ hlcWindow, hlcDevice };
		vector<HlcGameObject> hlcGameObjects;
	};
}
