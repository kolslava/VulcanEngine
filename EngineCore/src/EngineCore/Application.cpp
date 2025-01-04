#include <EngineCore/Application.hpp>

#include <EngineCore/Window.hpp>
#include <EngineCore/VulkanRender.hpp>

#include <EngineCore/EventManager.hpp>

#include <EngineCore/Logger.hpp>


namespace EngineCore {
	Application::Application() {
		//m_pWindow = std::make_unique<Window>(800, 600, "EngineCore");
		eventManager = std::make_unique<EventManager>();
		m_params = std::make_shared<WindowParams>();
		m_params->width = 400;
		m_params->height = 600;
		m_params->title = "EngineCore";

		m_pWindow = std::make_unique<Window>(m_params);

		m_params->eventCallback = [this](const AbstractEvent& event) {
			eventManager->dispatch(event);
		};

		eventManager->addHandler("MouseMoveEvent", [](const AbstractEvent& event) {
			const auto& mouseEvent = static_cast<const MouseMoveEvent&>(event);
			LOG_INFO("Mouse moved to: ({0}, {1})", mouseEvent.mouseX, mouseEvent.mouseY);
			});

		eventManager->addHandler("WindowResizeEvent", [](const AbstractEvent& event) {
			const auto& resizeEvent = static_cast<const WindowResizeEvent&>(event);
			LOG_INFO("Window resized to: ({0}, {1})", resizeEvent.width, resizeEvent.height);
			});

		eventManager->addHandler("KeyPressEvent", [](const AbstractEvent& event) {
			const auto& keyEvent = static_cast<const KeyPressEvent&>(event);
			LOG_INFO("Key pressed: {0}", keyEvent.keyCode);
			});

		eventManager->addHandler("KeyReleaseEvent", [](const AbstractEvent& event) {
			const auto& keyEvent = static_cast<const KeyReleaseEvent&>(event);
			LOG_INFO("Key released: {0}", keyEvent.keyCode);
			});

		eventManager->addHandler("MousePressEvent", [](const AbstractEvent& event) {
			const auto& mouseEvent = static_cast<const MousePressEvent&>(event);
			LOG_INFO("Mouse button pressed: {0}", mouseEvent.mouseButton);
			});

		eventManager->addHandler("MouseReleaseEvent", [](const AbstractEvent& event) {
			const auto& mouseEvent = static_cast<const MouseReleaseEvent&>(event);
			LOG_INFO("Mouse button released: {0}", mouseEvent.mouseButton);
			});

		eventManager->addHandler("WindowCloseEvent", [](const AbstractEvent& event) {
			LOG_INFO("Window closed");
			});
	}

	Application::~Application() {

	}

	void Application::Run() {
		try {
           while (!m_pWindow->shouldClose()) {
				m_pWindow->pollEvents();
				OnImGuiRender();
			}
		}
		catch (const std::exception& e) {
			LOG_CRITICAL("Exception: {0}", e.what());
		}
	}
}