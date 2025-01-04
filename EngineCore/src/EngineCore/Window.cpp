#include <EngineCore/Window.hpp>
#include <EngineCore/EventManager.hpp>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>

namespace EngineCore {
    
    // Constructor
    Window::Window(int w, int h, std::string t) {
		m_params = std::make_shared<WindowParams>();
		m_params->width = w;
		m_params->height = h;
		m_params->title = t;
        initGLFW();
        createWindow();
    }

    Window::Window(std::shared_ptr<WindowParams> params) {
		m_params = params;
		initGLFW();
		createWindow();
    }

    // Destructor
    Window::~Window() {
        if (window) {
            glfwDestroyWindow(window.get());
        }
        glfwTerminate();
    }

    GLFWwindow* Window::get() const {
        return window.get();
    }

    bool Window::shouldClose() const {
        return glfwWindowShouldClose(window.get());
    }

    void Window::pollEvents() const {
        glfwPollEvents();
    }

    // Initialize GLFW
    void Window::initGLFW() {
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW");
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // No OpenGL context
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);   // Allow resizing
    }

    // Create the GLFW window
    void  Window::createWindow() {
        GLFWwindow* rawWindow = glfwCreateWindow(m_params->width, m_params->height, m_params->title.c_str(), nullptr, nullptr);
        if (!rawWindow) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }
        window.reset(rawWindow);

        glfwSetWindowUserPointer(window.get(), this);
        glfwSetFramebufferSizeCallback(window.get(), framebufferResizeCallback);
        glfwSetCursorPosCallback(window.get(), mouseMoveCallback);
        glfwSetWindowCloseCallback(window.get(), windowCloseCallback);
        glfwSetKeyCallback(window.get(), keyCallback);
        glfwSetMouseButtonCallback(window.get(), mouseButtonCallback);
    }

    void Window::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
        auto appWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        if (appWindow && appWindow->m_params->eventCallback) {
            WindowResizeEvent event(width, height);
            appWindow->m_params->eventCallback(event);
        }
    }

    void Window::mouseMoveCallback(GLFWwindow* window, double xPos, double yPos) {
        auto appWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        if (appWindow && appWindow->m_params->eventCallback) {
            MouseMoveEvent event(xPos, yPos);
            appWindow->m_params->eventCallback(event);
        }
    }

    void Window::windowCloseCallback(GLFWwindow* window) {
        auto appWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        if (appWindow && appWindow->m_params->eventCallback) {
            WindowCloseEvent event;
            appWindow->m_params->eventCallback(event);
			//event.executeClose(window);
        }
    }

    void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        auto appWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        if (appWindow && appWindow->m_params->eventCallback) {
            if (action == GLFW_PRESS) {
                KeyPressEvent event(key);
                appWindow->m_params->eventCallback(event);
            }
            else if (action == GLFW_RELEASE) {
                KeyReleaseEvent event(key);
                appWindow->m_params->eventCallback(event);
            }
        }
    }

    void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
        auto appWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        if (appWindow && appWindow->m_params->eventCallback) {
            if (action == GLFW_PRESS) {
                MousePressEvent event(button);
                appWindow->m_params->eventCallback(event);
            }
            else if (action == GLFW_RELEASE) {
                MouseReleaseEvent event(button);
                appWindow->m_params->eventCallback(event);
            }
        }
    }

    void Window::GLFWDeleter::operator()(GLFWwindow* ptr) const {
		glfwDestroyWindow(ptr);
    }

}