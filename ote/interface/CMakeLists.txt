
add_library(distortion-interfaces INTERFACE)
target_include_directories(
        distortion-interfaces INTERFACE . ${CMAKE_CURRENT_BINARY_DIR}
)