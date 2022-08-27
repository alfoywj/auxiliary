
add_library(ote-interfaces INTERFACE)
target_include_directories(
        ote-interfaces INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
)