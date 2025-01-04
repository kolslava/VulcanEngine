#include <EngineCore/Application.hpp>

#include <iostream>
#include <string>
#include <memory>

class EngineEditor : public EngineCore::Application {

public:
	EngineEditor() {
		
	}
	~EngineEditor() {

	}
	void OnImGuiRender() override {
		//std::cout << "EngineEditor::OnImGuiRender()" << std::endl;
	}
};

int main(int argc, char* argv[]) {
	
	auto pEditorApp = std::make_unique<EngineEditor>();
	pEditorApp->Run();

	//std::cout << "Hello, World!" << std::endl;
	//std::cin.get();
	
	return 0;
}