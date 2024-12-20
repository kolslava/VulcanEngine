// main.cpp
#include <EngineCore/Engine.hpp>

class EngineEditor : public EngineCore::Engine {
protected:
    void renderImGui() override {
        ImGui::Begin("Hello, Vulkan!");
        ImGui::Text("Welcome to the Vulkan ImGui demo!");
        ImGui::End();
    }
};

int main() {
    try {
        EngineEditor app;
        app.Initialize();
        app.Run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}