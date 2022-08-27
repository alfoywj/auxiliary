

add_library(imgui STATIC
        imgui/imgui.h
        imgui/imgui.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_widgets.cpp
        imgui/backends/imgui_impl_vulkan.cpp
        imgui/backends/imgui_impl_sdl.cpp
        )

target_link_libraries(imgui
        PUBLIC
        Vulkan::Vulkan
        ${SDL2_LIBRARIES})
target_include_directories(imgui
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends
        ${SDL2_INCLUDE_DIRS})


# OpenXR
add_library(ote-external-openxr INTERFACE)
target_include_directories(
        ote-external-openxr INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/openxr_includes
)
