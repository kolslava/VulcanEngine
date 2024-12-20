// Engine.hpp
#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_vulkan.h>

#include <stdexcept>
#include <iostream>
#include <memory>

#include <vector>

class Engine {
public:
    Engine();
    virtual ~Engine();

    void initialize();
    void run();
    void cleanup();

protected:
    virtual void renderImGui();

private:
    void initWindow();
    void initVulkan();
    void mainLoop();

    VkCommandBuffer beginSingleTimeCommands();
    void endSingleTimeCommands(VkCommandBuffer commandBuffer);

    GLFWwindow* window;
    VkInstance instance;
    VkCommandPool commandPool; // You need to initialize this in initVulkan()
    VkQueue graphicsQueue;    // You need to initialize this in initVulkan()
    
    VkPhysicalDevice physicalDevice;
    VkDevice device;
    VkDescriptorPool descriptorPool;

    VkRenderPass renderPass;
};

#endif // ENGINE_HPP