// Engine.hpp
#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <iostream>
#include <memory>
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

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
        void initVulkan();
        void mainLoop();

    private:
        GLFWwindow* m_window;
        VkInstance instance;
    };

}

#endif // ENGINE_HPP