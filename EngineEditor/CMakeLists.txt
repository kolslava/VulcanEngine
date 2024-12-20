add_executable(EngineEditor src/main.cpp)

# Include EngineCore and ImGui
target_link_libraries(EngineEditor PRIVATE EngineCore)

# Include directories for ImGui (optional if needed directly in EngineEditor)
target_include_directories(EngineEditor PRIVATE
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)
