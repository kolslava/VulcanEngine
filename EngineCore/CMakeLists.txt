cmake_minimum_required(VERSION 3.12)

set(ENGINE_PROJECT_NAME EngineCore)

set(ENGINE_PUBLIC_INCLUDES
    includes/EngineCore/Application.hpp
)

set(ENGINE_PRIVATE_INCLUDES
    src/EngineCore/Window.hpp
)

set(ENGINE_PRIVATE_SOURCES
    src/EngineCore/Application.cpp
    src/EngineCore/Window.cpp
)

set(ENGINE_ALL_SOURCES
    ${ENGINE_PUBLIC_INCLUDES}
    ${ENGINE_PRIVATE_INCLUDES}
    ${ENGINE_PRIVATE_SOURCES}
)

add_library(${ENGINE_PROJECT_NAME} STATIC
    ${ENGINE_ALL_SOURCES}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
    ${ENGINE_ALL_SOURCES}
)

target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC includes)
target_include_directories(${ENGINE_PROJECT_NAME} PRIVATE src)
target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_17)

# GLFW
add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glfw)

# Vulkan
find_package(Vulkan REQUIRED)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE Vulkan::Vulkan)

# glm
add_subdirectory(../external/glm ${CMAKE_CURRENT_BINARY_DIR}/glm)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glm)

# ImGui
set(IMGUI_INCLUDES
    ../external/imgui/imgui.h
    ../external/imgui/backends/imgui_impl_vulkan.h
    ../external/imgui/backends/imgui_impl_glfw.h
)

set(IMGUI_SOURCES
    ../external/imgui/imgui.cpp
    ../external/imgui/backends/imgui_impl_vulkan.cpp
    ../external/imgui/backends/imgui_impl_glfw.cpp
    ../external/imgui/imgui_demo.cpp
    ../external/imgui/imgui_tables.cpp
    ../external/imgui/imgui_widgets.cpp
    ../external/imgui/imgui_draw.cpp
)

add_library(ImGui STATIC
    ${IMGUI_INCLUDES}
    ${IMGUI_SOURCES}
)

target_include_directories(ImGui PUBLIC ../external)
target_include_directories(ImGui PUBLIC ../external/imgui)
target_link_libraries(ImGui PRIVATE Vulkan::Vulkan glfw)

target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE ImGui)
