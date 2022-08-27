//
// Created by redbean on 22. 8. 25.
//
#include "usecase_interface.h"
#include "distortion_operation.h"
#include "render_interface.h"

void create_distortion_data_render(distortion_data_render *pDistortionDataRender,
                                   const uint32_t size_x,
                                   const uint32_t size_y){

    create_distortion_data(&pDistortionDataRender->oteGridMesh, size_x, size_y);
}

