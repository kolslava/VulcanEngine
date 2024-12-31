

struct GLFWwindow;

namespace EngineCore {

	class Window {
	private:
		GLFWwindow* m_pWindow;

		struct WindowData {
			const char* title;
			unsigned int width;
			unsigned int height;
		} mData;

	public:
		Window();
		virtual ~Window();

		//WindowData* GetWindowData() { return &mData; }

		void PollEvents();
		bool IsOpen() const;

	private:
		void Init();

		

		void Shutdown();


	};

}