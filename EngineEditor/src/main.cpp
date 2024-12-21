// main.cpp

#include <iostream>
#include <memory>
#include <imgui/imgui.h>

#include <EngineCore/Application.hpp>

class EngineEditor : public EngineCore::Application {

};

int main() {
    try {
        auto app = std::make_unique<EngineEditor>();
        app->run();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}