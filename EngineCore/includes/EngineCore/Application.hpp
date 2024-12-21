#define APPLICATION_HPP
#ifdef APPLICATION_HPP

#include <memory>
#include <iostream>
#include <stdexcept>
#include <cstdint>

struct GLFWwindow;

namespace EngineCore {

    class Application {
    public:
        Application();
        virtual ~Application();

        // Забороняємо копіювання та переміщення
        Application(const Application&) = delete;
        Application(Application&&) = delete;
        Application& operator=(const Application&) = delete;
        Application& operator=(Application&&) = delete;

        void run();

    private:
        void initWindow();
        void initVulkan();
        void mainLoop();
        void cleanup();

        GLFWwindow* window = nullptr;

        static const uint32_t WIDTH = 800;
        static const uint32_t HEIGHT = 600;
    };

}

#endif // APPLICATION_HPP
