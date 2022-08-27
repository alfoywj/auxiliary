
add_library(ote-operation STATIC
        distortion_operation.cpp
        distortion_operation.h
        )

target_include_directories(ote-operation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(ote-operation
        PUBLIC
        ote-interfaces)