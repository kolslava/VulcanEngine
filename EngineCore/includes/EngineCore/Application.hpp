
#include <memory>

namespace EngineCore {
	
	class Application {
	public:
		Application();
		virtual ~Application();

		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;
		Application(Application&&) = delete;
		Application& operator=(Application&&) = delete;

		void Run();

		virtual void OnImGuiRender() = 0;

	protected:
	std::shared_ptr<struct WindowParams> m_params;

	private:
		std::unique_ptr<class Window> m_pWindow;
		std::unique_ptr<class EventManager> eventManager;
		
		bool isRunning = true;

		//std::unique_ptr<VulkanRender> m_pVulkanRender;
		
	};

}