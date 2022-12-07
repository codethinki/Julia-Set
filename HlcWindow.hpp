#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace hlc {
	class HlcWindow {
	public:
		HlcWindow(int width, int height, std::string name);
		~HlcWindow();
		HlcWindow(const HlcWindow&) = delete;
		HlcWindow& operator=(const HlcWindow&) = delete;
		[[nodiscard]] bool windowResized() const { return framebufferResized; }
		void resetWindowResized() { framebufferResized = false; }

		bool shouldClose() { return glfwWindowShouldClose(hlcWindow); }

		VkExtent2D getExtent() { return { static_cast<uint32_t>(width), static_cast<uint32_t>(height) }; }

		void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

		bool w = false, a = false, s = false, d = false, down = false, up = false, left = false, right = false, space = false, mLeft = false, mRight = false;
		double yScroll = 0, mouseX = 0, mouseY = 0;
	private:
		static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

		void keyCallback(int key, int scan_code, int action, int mods);
		static void staticKeyCallback(GLFWwindow* window, int key, int scan_code, int action, int mods);

		void mouseMovementCallback(double xPos, double yPos);
		static void staticMouseMovementCallback(GLFWwindow* window, double xPos, double yPos);

		void mouseButtonCallback(int button, int action);
		static void staticMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

		void scrollCallback(double x_offset, double y_offset);
		static void staticScrollCallback(GLFWwindow* window, double x_offset, double y_offset);

		int width;
		int height;
		bool framebufferResized = false;

		std::string windowName;
		GLFWwindow* hlcWindow;

		void initWindow();

	};
}