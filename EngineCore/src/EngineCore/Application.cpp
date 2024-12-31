#include <EngineCore/Application.hpp>
#include <EngineCore/Logger.hpp>
#include <EngineCore/Window.hpp>
#include <EngineCore/VulkanRender.hpp>

namespace EngineCore {
	Application::Application() {
		this->m_pWindow = std::make_unique<Window>();
		this->m_pRenderer = std::make_unique<VulkanRender>();

		m_pRenderer->Init();
	}

	Application::~Application() {
	}

	void Application::Run() {
		try {
			while (m_pWindow->IsOpen()) {
				m_pWindow->PollEvents();
				//Render
				m_pRenderer->Render();
			}
		}
		catch (const std::exception& e) {
			LOG_CRITICAL("Exception: {0}", e.what());
		}
	}
}