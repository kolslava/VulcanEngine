
#include <EngineCore/Application.hpp>

#include <iostream>
#include <string>
#include <memory>

class EngineEditor : public EngineCore::Application {
private:


public:


};

int main(int argc, char* argv[]) {

	auto pApp = std::make_unique<EngineEditor>();

	pApp->Run();

	return 0;
}