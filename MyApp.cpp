#include "MyApp.hpp"
#include "HlcSimpleRS.hpp"
#include <glm/glm.hpp>
#include <fstream>
#include <chrono>
#include "stuff/windowsStuff.hpp"
#include "stuff/fileworkStuff.hpp"
#include "stuff/stringStuff.hpp"
namespace hlc {
	using namespace std;
	using namespace chrono;

	std::unique_ptr<HlcModel> createSquareModel(HlcDevice& device, const glm::vec2 position, const glm::vec2 extent) {
		std::vector<HlcModel::Vertex> vertices = {
			{{0.f, 0.f}},
			{{extent.x, extent.y}},
			{{0.f, extent.y}},
			{{0.f, 0.f}},
			{{extent.x, 0.f}},
			{{extent.x, extent.y}},
		};
		for (auto& v : vertices) {
			v.position += position;
		}
		return std::make_unique<HlcModel>(device, vertices);
	}

	void saveSeed(const glm::vec2 seed) {
		const wstring content = wreadFile(L"seeds/savedSeeds.txt", false);
		wstring output(L"seed: " + to_wstring(seed.x) + L" + i(" + to_wstring(seed.y) + L")");

		if (hlc::wfindInFile(L"seeds/savedSeeds.txt", output) == 0) {
			wofstream file("seeds/savedSeeds.txt", ios::app);
			output += L"\n";
			file.write(output.c_str(), output.size());
			file.close();
		}
	}
	bool loadSeed(glm::vec2& vec) {
		wstring seed = wreadFile(L"seeds/startSeed.txt", false);
		if (seed.empty()) return false;
		vector<wstring> numbers = wsplit(seed, L"+");
		if (numbers.size() != 2) return false;
		toNumber(numbers[0]);
		toNumber(numbers[1]);
		vec.x = stof(numbers[0]);
		vec.y = stof(numbers[1]);
		return true;
	}

	MyApp::MyApp() {}
	MyApp::~MyApp() {}

	void MyApp::run() {

		const shared_ptr squareModel = createSquareModel(hlcDevice, { -1.f, -1.f }, { 2.f, 2.f });
		auto square = HlcGameObject::createGameObject();
		square.model = squareModel;

		SimpleRenderSystem simpleRenderSystem{ hlcDevice, hlcRenderer.getSwapchainRenderPass(), hlcDevice.wideShader };

		if(!loadSeed(simpleRenderSystem.cOffset)) {
			messageBox(L"Error", L"failed to load seed", MB_OK | MB_ICONWARNING);
			wofstream file(L"seeds/startSeed.txt", ofstream::trunc);
			const wstring defaultSeed(L"seed: 0.000000 + i(0.000000)");
			file.write(defaultSeed.c_str(), defaultSeed.size());
			file.close();
		}

		constexpr double zoomSpeed = 0.03, moveSpeed = 0.05;
		double zoom = 1, zoomY = 0, zoomX = 0;
		constexpr float extent = 2;
		double x = 0, y = 0;
		bool save = false;
		while (!hlcWindow.shouldClose()) {
			if (hlcWindow.space) {
				if (messageBox(L"Save", L"save this seed?", MB_ICONQUESTION | MB_YESNO) == IDYES) {
					saveSeed(simpleRenderSystem.cOffset);
				}
			}

			glfwPollEvents();
			const auto commandBuffer = hlcRenderer.beginFrame();
			if (commandBuffer != nullptr) {
				//update System
				if (hlcWindow.w) zoomY -= moveSpeed / zoom;
				if (hlcWindow.s) zoomY += moveSpeed / zoom;
				if (hlcWindow.a) zoomX -= moveSpeed / zoom;
				if (hlcWindow.d) zoomX += moveSpeed / zoom;
				simpleRenderSystem.windowSize = hlcWindow.getExtent();
				const double ratio = static_cast<double>(simpleRenderSystem.windowSize.width) / simpleRenderSystem.windowSize.height;

				//simpleRenderSystem.cOffset = glm::vec2((hlcWindow.mouseX - simpleRenderSystem.windowSize.width/2)/1000, (hlcWindow.mouseY - simpleRenderSystem.windowSize.height/2)/1000);
				if (hlcWindow.left) simpleRenderSystem.cOffset.x -= .01 / pow(zoom, 2);
				if (hlcWindow.right) simpleRenderSystem.cOffset.x += .01 / pow(zoom, 2);
				if (hlcWindow.down) simpleRenderSystem.cOffset.y -= .01 / pow(zoom, 2);
				if (hlcWindow.up) simpleRenderSystem.cOffset.y += .01 / pow(zoom, 2);

				if (hlcWindow.mRight) simpleRenderSystem.detail > 1 ? simpleRenderSystem.detail-- : 0;
				if (hlcWindow.mLeft) simpleRenderSystem.detail++;

				if (hlcWindow.yScroll != 0) {
					zoom *= 1 + zoomSpeed * hlcWindow.yScroll * 3;
					hlcWindow.yScroll = 0;
				}

				simpleRenderSystem.extent = glm::vec4(zoomX - 2 * ratio / zoom, zoomX + 2 * ratio / zoom, zoomY - 2 / zoom, zoomY + 2 / zoom);

				//render
				hlcRenderer.beginSwapchainRenderPass(commandBuffer);
				simpleRenderSystem.renderSquare(commandBuffer, square);
				hlcRenderer.endSwapchainRenderPass(commandBuffer);
				hlcRenderer.endFrame();
			}
		}
		vkDeviceWaitIdle(hlcDevice.device());
	}
}
