#include <EngineCore/Window.hpp>
#include <EngineCore/Logger.hpp>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace EngineCore {
	Window::Window() {
		m_pWindow = nullptr;
		mData = {
			"Vulkan",
			800,
			600,
		};

		Init();
	}
	
	Window::~Window() {
		Shutdown();
	}

	void Window::Init() {
		if (!glfwInit()) {
			LOG_CRITICAL("Failed to initialize GLFW");
			return;
		}

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		m_pWindow = glfwCreateWindow(mData.width, mData.height, mData.title, nullptr, nullptr);

		if (!m_pWindow) {
			LOG_CRITICAL("Failed to create GLFW window");
			return;
		}


		LOG_INFO("Window \"{}\" created ({}x{})", mData.title, mData.width, mData.height);
	}
	
	void Window::PollEvents() {
		glfwPollEvents();
	}

	bool Window::IsOpen() const {
		return !glfwWindowShouldClose(m_pWindow);
	}

	void Window::Shutdown() {
		glfwDestroyWindow(m_pWindow);
		glfwTerminate();
		LOG_INFO("Window destroyed");
	}
}