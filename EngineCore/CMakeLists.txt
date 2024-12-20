add_library(EngineCore STATIC)

target_sources(EngineCore
    PRIVATE
        src/EngineCore/Engine.cpp
    PUBLIC
        include
)

target_include_directories(EngineCore PUBLIC include)
target_link_libraries(EngineCore PUBLIC Vulkan::Vulkan glm glfw)
