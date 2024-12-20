#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <iostream>
#include <vector>
#include <stdexcept>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

// ImGui
#include <imgui.h>
#include <imgui_impl_vulkan.h>
#include <imgui_impl_glfw.h>

namespace EngineCore {

    class Engine {
    public:
        Engine();
        virtual ~Engine();

        void Initialize();
        void Run();
        void Cleanup();

    protected:
        virtual void renderImGui();

    private:
        void initWindow();
        void CreateInstance();
        void pickPhysicalDevice();
        void createLogicalDevice();
        void createDescriptorPool();
        void createCommandPool();
        void createCommandBuffer();
        void createRenderPass();
        void initVulkan();
        void initImGui();
        void cleanupImGui();
        void mainLoop();

        VkCommandBuffer beginSingleTimeCommands();
        void endSingleTimeCommands(VkCommandBuffer);

    private:
        GLFWwindow* m_window;
        VkInstance instance;
        VkPhysicalDevice physicalDevice;
        VkDevice device;
        VkQueue graphicsQueue;
        VkSurfaceKHR surface;

        VkRenderPass renderPass;
        VkCommandPool commandPool;
        VkCommandBuffer commandBuffer;
        VkDescriptorPool imguiDescriptorPool;
    };

}

#endif // ENGINE_HPP