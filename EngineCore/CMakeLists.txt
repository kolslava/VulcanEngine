add_library(EngineCore STATIC)

# Sources for EngineCore
target_sources(EngineCore
    PRIVATE
        src/EngineCore/Engine.cpp
    PUBLIC
        include
)

# Include directories
target_include_directories(EngineCore PUBLIC include)

# Dependencies
target_link_libraries(EngineCore PUBLIC Vulkan::Vulkan glfw glm)

# Add ImGui sources
set(IMGUI_SRC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_vulkan.cpp
)

target_sources(EngineCore PRIVATE ${IMGUI_SRC})

target_include_directories(EngineCore PRIVATE
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)
