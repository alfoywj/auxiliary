//
// Created by redbean on 22. 8. 25.
//
#include "usecase_interface.h"
#include "distortion_operation.h"
#include "render_interface.h"

void create_distortion_data_render(VkBundle *vk, distortion_data_render *pDistortionDataRender, const uint32_t size_y,
                                   const uint32_t size_x) {

    create_distortion_data(&pDistortionDataRender->oteGridMesh, size_x, size_y);

    create_render_mesh(vk, &pDistortionDataRender->oteGridMesh.dataMesh, &pDistortionDataRender->renderMesh);
}

void update_distortion_data_render(VkBundle *vk, ote_radial radial, distortion_data_render *pDistortionDataRender) {
    update_distortion_data(radial, &pDistortionDataRender->oteGridMesh);
    update_render_mesh(vk,&pDistortionDataRender->oteGridMesh.dataMesh, &pDistortionDataRender->renderMesh);
}

