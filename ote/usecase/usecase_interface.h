#pragma once

#include "render_interface.h"
#include "distortion_operation.h"

#ifdef __cplusplus
extern "C" {
#endif

struct distortion_data_render {
    ote_grid_mesh oteGridMesh;
    render_mesh renderMesh;
};

void create_distortion_data_render(distortion_data_render *pDistortionDataRender, const uint32_t size_x, const uint32_t size_y);

#ifdef __cplusplus
}
#endif