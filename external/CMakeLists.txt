
add_subdirectory(imgui)


# OpenXR
add_library(ote-external-openxr INTERFACE)
target_include_directories(
        ote-external-openxr INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/openxr_includes
)
