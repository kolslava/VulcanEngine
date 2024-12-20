// main.cpp
#include "EngineCore/Engine.hpp"

class EngineEditor : public Engine {
protected:
    void renderImGui() override {
        ImGui::ShowDemoWindow();
    }
};

int main() {
    try {
        std::unique_ptr<EngineEditor> app = std::make_unique<EngineEditor>();
        app->initialize();
        app->run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
