#include <EngineCore/VulkanRender.hpp>
#include <EngineCore/Logger.hpp>

#include <vulkan/vulkan.h>

namespace EngineCore {
	VulkanRender::VulkanRender() : m_pInstance(VK_NULL_HANDLE) {}

	VulkanRender::~VulkanRender() {
		Cleanup();
	}
	void VulkanRender::Init() {
		LOG_INFO("Initializing Vulkan Renderer...");
		CreateInstance();
	}
	void VulkanRender::Render() {
		//LOG_INFO("Rendering frame...");
	}
	void VulkanRender::Cleanup() {
		if (m_pInstance != VK_NULL_HANDLE) {
			vkDestroyInstance(m_pInstance, nullptr);
			LOG_INFO("Vulkan instance destroyed");
		}
	}
	void VulkanRender::CreateInstance() {
        SPDLOG_INFO("Creating Vulkan instance...");

        // Інформація про додаток
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Engine App";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "EngineCore";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_3;

        // Інформація про створення інстансу
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        // Отримання доступних розширень Vulkan
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        LOG_INFO("Available Vulkan extensions:");
        for (const auto& extension : extensions) {
            SPDLOG_INFO("  - {}", extension.extensionName);
        }

        // Перевірка наявності необхідних розширень
        std::vector<const char*> requiredExtensions = {
            VK_KHR_SURFACE_EXTENSION_NAME,
            #ifdef __APPLE__
                    "VK_MVK_macos_surface" // Розширення для macOS
            #else
                    "VK_KHR_win32_surface" // Розширення для Windows
            #endif
        };

        createInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
        createInfo.ppEnabledExtensionNames = requiredExtensions.data();

        // Створення Vulkan Instance
        if (vkCreateInstance(&createInfo, nullptr, &m_pInstance) != VK_SUCCESS) {
            SPDLOG_CRITICAL("Failed to create Vulkan instance");
            throw std::runtime_error("Failed to create Vulkan instance");
        }

        LOG_INFO("Vulkan instance created successfully");
	}
}