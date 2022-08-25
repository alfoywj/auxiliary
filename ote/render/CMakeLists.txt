
add_library(distortion-render-interfaces STATIC
        render_interface.h
        render_interface.cpp
        render_distortion.cpp
        )

target_link_libraries(distortion-render-interfaces PUBLIC distortion-interfaces)