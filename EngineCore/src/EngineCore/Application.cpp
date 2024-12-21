#include <EngineCore/Application.hpp>

#include <iostream>
#include <vector>
#include <stdexcept>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

// ImGui
#include <imgui.h>
#include <imgui/backends/imgui_impl_vulkan.h>
#include <imgui/backends/imgui_impl_glfw.h>

namespace EngineCore {

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

}