
add_library(ote-usecase STATIC
        usecase_interface.h
        usecase_interface.cpp
        )
target_include_directories(ote-usecase PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(ote-usecase
        PUBLIC
        ote-operation
        ote-render)