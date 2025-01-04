#pragma once

#include <memory>
#include <string>
#include <vector>
#include <functional>
#include <stdexcept>

struct GLFWwindow;

namespace EngineCore {

    // Structure to hold window parameters
    struct WindowParams {
        std::string title;
        int width;
        int height;
        std::function<void(const class AbstractEvent&)> eventCallback;
    };

    class Window {
    public:
        // Constructor
        Window(int, int, std::string);
		Window(std::shared_ptr<WindowParams> params);

        // Destructor
        virtual ~Window();

        // Accessor for the raw GLFWwindow pointer
        GLFWwindow* get() const;

        // Check if the window should close
        bool shouldClose() const;

        void pollEvents() const;

    private:
        struct GLFWDeleter {
            void operator()(GLFWwindow* ptr) const;
        };

        std::unique_ptr<GLFWwindow, GLFWDeleter> window;
		std::shared_ptr<WindowParams> m_params;

        // Initialize GLFW
        void initGLFW();

        // Create the GLFW window
        void createWindow();

        static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
        static void mouseMoveCallback(GLFWwindow* window, double xPos, double yPos);
        static void windowCloseCallback(GLFWwindow* window);

        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    };
}