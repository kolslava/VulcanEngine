
#include <string>
#include <functional>
#include <unordered_map>
#include <vector>

#include <EngineCore/Logger.hpp>

//struct GLFWwindow;

namespace EngineCore {
    // Abstract base class for events
    class AbstractEvent {
    public:
        virtual ~AbstractEvent() = default;
        virtual const char* getName() const = 0;
    };

    // Specific event classes
    class MouseMoveEvent : public AbstractEvent {
    public:
        MouseMoveEvent(double x, double y) : mouseX(x), mouseY(y) {}
        const char* getName() const override { return "MouseMoveEvent"; }
        double mouseX, mouseY;
    };

    class WindowResizeEvent : public AbstractEvent {
    public:
        WindowResizeEvent(int w, int h) : width(w), height(h) {}
        const char* getName() const override { return "WindowResizeEvent"; }
        int width, height;
    };

    class WindowCloseEvent : public AbstractEvent {
    public:
        const char* getName() const override { return "WindowCloseEvent"; }
        //void executeClose(GLFWwindow* window) const;
    };

    class KeyPressEvent : public AbstractEvent {
    public:
        KeyPressEvent(int key) : keyCode(key) {}
        const char* getName() const override { return "KeyPressEvent"; }
        int keyCode;
    };

    class KeyReleaseEvent : public AbstractEvent {
    public:
        KeyReleaseEvent(int key) : keyCode(key) {}
        const char* getName() const override { return "KeyReleaseEvent"; }
        int keyCode;
    };

    class MousePressEvent : public AbstractEvent {
    public:
        MousePressEvent(int button) : mouseButton(button) {}
        const char* getName() const override { return "MousePressEvent"; }
        int mouseButton;
    };

    class MouseReleaseEvent : public AbstractEvent {
    public:
        MouseReleaseEvent(int button) : mouseButton(button) {}
        const char* getName() const override { return "MouseReleaseEvent"; }
        int mouseButton;
    };

    // Event manager
    class EventManager {
    public:
        using EventHandler = std::function<void(const AbstractEvent&)>;

        void addHandler(const std::string& eventName, EventHandler handler) {
            handlers[eventName].push_back(handler);
        }

        void dispatch(const AbstractEvent& event) {
            const auto& eventName = event.getName();
            if (handlers.find(eventName) != handlers.end()) {
                for (const auto& handler : handlers[eventName]) {
                    try {
                        handler(event);  // Виклик обробника
                    }
                    catch (const std::exception& e) {
                        LOG_CRITICAL("Error in handler for event ", eventName, ": ", e.what());
                    }
                }
            }
            else {
                LOG_CRITICAL("No handlers for event: ", eventName);
            }
        }

    private:
        std::unordered_map<std::string, std::vector<EventHandler>> handlers;
    };
}