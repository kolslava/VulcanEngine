// main.cpp

#include <iostream>
#include <memory>
#include <imgui/imgui.h>

#include <EngineCore/Application.hpp>

class EngineEditor : public EngineCore::Application {

};

int main() {

	auto pEngineEditorApp = std::make_unique<EngineEditor>();

	std::cin.get();

	return 0;
}