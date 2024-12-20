// main.cpp
#include <EngineCore/Engine.hpp>

class EngineEditor : public EngineCore::Engine {
protected:
    void renderImGui() override {
        // Custom ImGui rendering can be implemented here.
    }
};

int main() {
    try {
        std::unique_ptr<EngineEditor> app = std::make_unique<EngineEditor>();
        app->Initialize();
        app->Run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}