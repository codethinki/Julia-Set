#pragma once
#pragma once

#include  "HlcDevice.hpp"
#include "HlcWindow.hpp"
#include "HlcSwapchain.hpp"

#include <memory>
#include <vector>
#include <cassert>
namespace hlc {
	using namespace std;
	class HlcRenderer {
	public:
		HlcRenderer(HlcWindow& window, HlcDevice& device);
		~HlcRenderer();

		HlcRenderer(const HlcRenderer&) = delete;
		HlcRenderer& operator=(const HlcRenderer&) = delete;

		[[nodiscard]] VkRenderPass getSwapchainRenderPass() const { return hlcSwapchain->getRenderPass(); }

		[[nodiscard]] bool frameInProgress() const { return frameStarted; }
		[[nodiscard]] VkCommandBuffer getCommandBuffer() const {
			assert(frameStarted && "getCommandBuffer: frame didn't start");
			return commandBuffers[currentFrameIndex];
		}
		int getFrameIndex() const {
			assert(frameStarted && "getFrameIndex: no frame in progress");
			return currentFrameIndex;
		}

		VkCommandBuffer beginFrame();
		void endFrame();
		void beginSwapchainRenderPass(VkCommandBuffer command_buffer);
		void endSwapchainRenderPass(VkCommandBuffer command_buffer);

	private:
		void createCommandBuffers();
		void freeCommandBuffers();
		void recreateSwapchain();

		static vector<char> readShaderFile(const string& filepath);

		HlcWindow& hlcWindow;
		HlcDevice& hlcDevice;
		unique_ptr<HlcSwapchain> hlcSwapchain;
		vector<VkCommandBuffer> commandBuffers;

		uint32_t currentImageIndex;
		int currentFrameIndex = 0;
		bool frameStarted = false;
	};
}