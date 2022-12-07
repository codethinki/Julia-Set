#include "HlcWindow.hpp"

#include <stdexcept>

namespace  hlc {

	HlcWindow::HlcWindow(int width, int height, std::string name) : width{ width }, height{ height }, windowName{ name } {
		initWindow();
	}
	HlcWindow::~HlcWindow() {
		glfwDestroyWindow(hlcWindow);
		glfwTerminate();
	}

	void HlcWindow::initWindow() {
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		hlcWindow = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(hlcWindow, this);
		glfwSetKeyCallback(hlcWindow, staticKeyCallback);
		glfwSetCursorPosCallback(hlcWindow, staticMouseMovementCallback);
		glfwSetMouseButtonCallback(hlcWindow, staticMouseButtonCallback);
		glfwSetScrollCallback(hlcWindow, staticScrollCallback);
		glfwSetFramebufferSizeCallback(hlcWindow, framebufferResizeCallback);
	}

	void HlcWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface) {
		if (glfwCreateWindowSurface(instance, hlcWindow, nullptr, surface) != VK_SUCCESS) throw std::runtime_error(
			"createWindowSurface: failed to create window surface");
	}

	void HlcWindow::staticKeyCallback(GLFWwindow* window, int key, int scan_code, int action, int mods) {
		const auto newHlcWindow = static_cast<HlcWindow*>(glfwGetWindowUserPointer(window));
		newHlcWindow->keyCallback(key, scan_code, action, mods);
	}
	void HlcWindow::keyCallback(const int key, int scan_code, const int action, int mods) {
		if (key == GLFW_KEY_W) w = action;
		if (key == GLFW_KEY_A) a = action;
		if (key == GLFW_KEY_S) s = action;
		if (key == GLFW_KEY_D) d = action;
		if (key == GLFW_KEY_UP) up = action;
		if (key == GLFW_KEY_DOWN) down = action;
		if (key == GLFW_KEY_LEFT) left = action;
		if (key == GLFW_KEY_RIGHT) right = action;
		if(key == GLFW_KEY_SPACE) space = action;
	}

	void HlcWindow::staticMouseMovementCallback(GLFWwindow* window, double xPos, double yPos) {
		const auto newHlcWindow = static_cast<HlcWindow*>(glfwGetWindowUserPointer(window));
		newHlcWindow->mouseX = xPos;
		newHlcWindow->mouseY = yPos;
	}
	void HlcWindow::staticMouseButtonCallback(GLFWwindow* window, const int button, const int action, int mods) {
		const auto newHlcWindow = static_cast<HlcWindow*>(glfwGetWindowUserPointer(window));
		newHlcWindow->mouseButtonCallback(button, action);
	}
	void HlcWindow::mouseButtonCallback(const int button, const int action) {
		if (button == GLFW_MOUSE_BUTTON_RIGHT) mRight = action;
		if (button == GLFW_MOUSE_BUTTON_LEFT) mLeft = action;
	}


	void HlcWindow::staticScrollCallback(GLFWwindow* window, double x_offset, double y_offset) {
		const auto newHlcWindow = static_cast<HlcWindow*>(glfwGetWindowUserPointer(window));
		newHlcWindow->scrollCallback(x_offset, y_offset);
	}
	void HlcWindow::scrollCallback(double x_offset, double y_offset) {
		yScroll = static_cast<int>(y_offset);
	}


	void HlcWindow::framebufferResizeCallback(GLFWwindow* window, const int width, const int height) {
		const auto newHlcWindow = static_cast<HlcWindow*>(glfwGetWindowUserPointer(window));
		newHlcWindow->framebufferResized = true;
		newHlcWindow->width = width;
		newHlcWindow->height = height;
	}
}
