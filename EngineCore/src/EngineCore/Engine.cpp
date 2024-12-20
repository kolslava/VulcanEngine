// Engine.cpp
#include <EngineCore/Engine.hpp>

namespace EngineCore {

    Engine::Engine() : m_window(nullptr), instance(VK_NULL_HANDLE) {}

    Engine::~Engine() {}

    void Engine::Initialize() {
        initWindow();
        initVulkan();
    }

    void Engine::Run() {
        mainLoop();
        Cleanup();
    }

    void Engine::Cleanup() {
        if (instance != VK_NULL_HANDLE) {
            vkDestroyInstance(instance, nullptr);
        }
        if (m_window) {
            glfwDestroyWindow(m_window);
            glfwTerminate();
        }
    }

    void Engine::renderImGui() {}

    void Engine::initWindow() {
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW!");
        }
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        m_window = glfwCreateWindow(600, 600, "Vulkan Window", nullptr, nullptr);
        if (!m_window) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window!");
        }
    }

    void Engine::CreateInstance() {
        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Vulkan";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "Super Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_3;

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        VkInstanceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        createInfo.enabledLayerCount = 0;

        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create Vulkan instance!");
        }
    }

    void Engine::initVulkan() {
        CreateInstance();
    }

    void Engine::mainLoop() {
        while (!glfwWindowShouldClose(m_window)) {
            glfwPollEvents();
        }
    }
}