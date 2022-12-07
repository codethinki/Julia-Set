#include "HlcRenderer.hpp"

#include <stdexcept>
#include <array>
#include <algorithm>
#include <fstream>
namespace hlc {
	HlcRenderer::HlcRenderer(HlcWindow& window, HlcDevice& device) : hlcWindow{ window }, hlcDevice{ device }, currentImageIndex{ 0 } {
		recreateSwapchain();
		createCommandBuffers();
	}
	HlcRenderer::~HlcRenderer() {
		freeCommandBuffers();
	}

	void HlcRenderer::recreateSwapchain() {
		auto extent = hlcWindow.getExtent();
		while (extent.width == 0 || extent.height == 0) {
			extent = hlcWindow.getExtent();
			glfwWaitEvents();
		}

		vkDeviceWaitIdle(hlcDevice.device());

		if (hlcSwapchain == nullptr) hlcSwapchain = make_unique<HlcSwapchain>(hlcDevice, extent);
		else {
			shared_ptr oldSwapchain = move(hlcSwapchain);
			hlcSwapchain = make_unique<HlcSwapchain>(hlcDevice, extent, oldSwapchain);
			if (!oldSwapchain->compareSwapFormats(*hlcSwapchain.get())) throw runtime_error(
				"recreateSwapchain: depth or image format changed");
		}

	}


	void HlcRenderer::createCommandBuffers() {
		commandBuffers.resize(hlcSwapchain->MAX_FRAMES_IN_FLIGHT);
		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = hlcDevice.getCommandPool();
		allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());
		if (vkAllocateCommandBuffers(hlcDevice.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS) throw runtime_error("createCommandBuffers: failed to create command buffers");
	};
	void HlcRenderer::freeCommandBuffers() {
		vkFreeCommandBuffers(hlcDevice.device(), hlcDevice.getCommandPool(), static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());
		commandBuffers.clear();
	}

	VkCommandBuffer HlcRenderer::beginFrame() {
		assert(!frameStarted && "beginFrame: can't begin 2 Frames at the same time");

		auto result = hlcSwapchain->acquireNextImage(&currentImageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR) {
			recreateSwapchain();
			return nullptr;
		}
		if (result != VK_SUCCESS && result !=
			VK_SUBOPTIMAL_KHR) throw runtime_error("begin Frame: failed to acquire swapchain image");

		frameStarted = true;

		auto commandBuffer = getCommandBuffer();
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) throw runtime_error("beginFrame: failed to begin recording command buffer");

		return commandBuffer;
	}
	void HlcRenderer::endFrame() {
		assert(frameStarted && "endFrame: can't end a non existing frame");
		auto commandBuffer = getCommandBuffer();
		if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) throw runtime_error("endFrame: failed to record command buffer");

		const auto result = hlcSwapchain->submitCommandBuffers(&commandBuffer, &currentImageIndex);
		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || hlcWindow.windowResized()) {
			hlcWindow.resetWindowResized();
			recreateSwapchain();
		}
		else if (result != VK_SUCCESS) throw runtime_error("endFrame: failed to present swapchain image");

		frameStarted = false;
		++currentFrameIndex %= HlcSwapchain::MAX_FRAMES_IN_FLIGHT;

	}

	void HlcRenderer::beginSwapchainRenderPass(const VkCommandBuffer command_buffer) {
		assert(frameStarted && "beginSwapchainRenderPass: can't write to non existing frame");
		assert(command_buffer == getCommandBuffer() && "beginSwapchainRenderPass: Can't begin two render passes at once");
		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = hlcSwapchain->getRenderPass();
		renderPassInfo.framebuffer = hlcSwapchain->getFrameBuffer(static_cast<int>(currentImageIndex));
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = hlcSwapchain->getSwapchainExtent();

		array<VkClearValue, 2> clearValues{};
		clearValues[0].color = { 0.0f, 0.0f, 0.0f, 1.0f };
		clearValues[1].depthStencil = { 1.0f, 0 };
		renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
		renderPassInfo.pClearValues = clearValues.data();

		vkCmdBeginRenderPass(command_buffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = static_cast<float>(hlcSwapchain->getSwapchainExtent().width);
		viewport.height = static_cast<float>(hlcSwapchain->getSwapchainExtent().height);
		viewport.minDepth = 0;
		viewport.maxDepth = 1.0f;
		VkRect2D scissor{ {0,0}, hlcSwapchain->getSwapchainExtent() };
		vkCmdSetViewport(command_buffer, 0, 1, &viewport);
		vkCmdSetScissor(command_buffer, 0, 1, &scissor);

	}
	void HlcRenderer::endSwapchainRenderPass(const VkCommandBuffer command_buffer) {
		assert(frameStarted && "endRenderPass: can't end a non existing frame");
		assert(command_buffer == getCommandBuffer() && "endRenderPass: Can't end other render passes");
		vkCmdEndRenderPass(command_buffer);
	}
}
