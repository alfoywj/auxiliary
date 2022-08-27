
add_library(ote-render STATIC
        render_interface.h
        render_interface.cpp
        )
target_include_directories(ote-render PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(ote-render
        PUBLIC
        ote-interfaces)