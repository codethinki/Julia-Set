#pragma once

#include "HlcDevice.hpp"

// vulkan headers
#include <vulkan/vulkan.h>

// std lib headers
#include <vector>
#include <memory>
namespace hlc {

	class HlcSwapchain {
	public:
		static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

		HlcSwapchain(HlcDevice& device_ref, VkExtent2D window_extent);
		HlcSwapchain(HlcDevice& device_ref, VkExtent2D window_extent, std::shared_ptr<HlcSwapchain> previous);
		~HlcSwapchain();

		HlcSwapchain(const HlcSwapchain&) = delete;
		HlcSwapchain& operator=(const HlcSwapchain&) = delete;

		VkFramebuffer getFrameBuffer(int index) { return swapchainFramebuffers[index]; }
		VkRenderPass getRenderPass() { return renderPass; }
		VkImageView getImageView(int index) { return swapchainImageViews[index]; }
		size_t imageCount() { return swapchainImages.size(); }
		VkFormat getSwapchainImageFormat() { return swapchainImageFormat; }
		VkExtent2D getSwapchainExtent() { return swapchainExtent; }
		uint32_t width() { return swapchainExtent.width; }
		uint32_t height() { return swapchainExtent.height; }

		float extentAspectRatio() {
			return static_cast<float>(swapchainExtent.width) / static_cast<float>(swapchainExtent.height);
		}
		VkFormat findDepthFormat();

		VkResult acquireNextImage(uint32_t* image_index);
		VkResult submitCommandBuffers(const VkCommandBuffer* buffers, const uint32_t* image_index);

		[[nodiscard]] bool compareSwapFormats(const HlcSwapchain& swapchain) const {
			return swapchain.swapchainDepthFormat == swapchainDepthFormat && swapchain.swapchainImageFormat ==
				swapchainImageFormat;
		}

	private:
		void init();
		void createSwapchain();
		void createImageViews();
		void createDepthResources();
		void createRenderPass();
		void createFramebuffers();
		void createSyncObjects();

		// Helper functions
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(
			const std::vector<VkSurfaceFormatKHR>& available_formats);
		VkPresentModeKHR chooseSwapPresentMode(
			const std::vector<VkPresentModeKHR>& available_present_modes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

		VkFormat swapchainImageFormat;
		VkFormat swapchainDepthFormat;
		VkExtent2D swapchainExtent;

		std::vector<VkFramebuffer> swapchainFramebuffers;
		VkRenderPass renderPass;

		std::vector<VkImage> depthImages;
		std::vector<VkDeviceMemory> depthImageMemorys;
		std::vector<VkImageView> depthImageViews;
		std::vector<VkImage> swapchainImages;
		std::vector<VkImageView> swapchainImageViews;

		HlcDevice& device;
		VkExtent2D windowExtent;

		VkSwapchainKHR swapchain;
		std::shared_ptr<HlcSwapchain> oldSwapchain;

		std::vector<VkSemaphore> imageAvailableSemaphores;
		std::vector<VkSemaphore> renderFinishedSemaphores;
		std::vector<VkFence> inFlightFences;
		std::vector<VkFence> imagesInFlight;
		size_t currentFrame = 0;
	};

}
