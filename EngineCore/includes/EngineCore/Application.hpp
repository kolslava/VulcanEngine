
#include <memory>

namespace EngineCore {
	class Application {
	public:
		Application();
		virtual ~Application();
		void Run();



	private:
		std::unique_ptr<class Window> m_pWindow;
		std::unique_ptr<class VulkanRender> m_pRenderer;
	};
}