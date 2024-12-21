















/*
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
        void createFramebuffers();
        void createRenderPass();

        void createSwapChain();
        bool isDeviceSuitable(VkPhysicalDevice);

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

        std::vector<VkFramebuffer> swapChainFramebuffers;
        std::vector<VkImageView> swapChainImageViews;
        VkExtent2D swapChainExtent;
        VkSwapchainKHR swapChain;

        uint32_t graphicsQueueFamilyIndex;
        uint32_t presentQueueFamilyIndex;

        VkQueue presentQueue;  // Черга для презентацій
        std::vector<VkImage> swapChainImages;          // Список зображень у SwapChain

        uint32_t currentFrame = 0;  // Індекс поточного кадру
        const int MAX_FRAMES_IN_FLIGHT = 2;
    };

}

#endif // ENGINE_HPP
*/