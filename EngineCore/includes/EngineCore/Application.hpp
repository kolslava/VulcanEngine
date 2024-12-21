#define APPLICATION_HPP
#ifdef APPLICATION_HPP

namespace EngineCore {

	class Application {
	public:
        Application();
        virtual ~Application();

        Application(const Application&) = delete;
        Application(Application&&) = delete;
        Application& operator=(const Application&) = delete;
        Application& operator=(Application&&) = delete;

        

	};

}

#endif // APPLICATION_HPP
