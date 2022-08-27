//
// Created by redbean on 22. 8. 27.
//

#ifndef DISTORTION_BROWN_MODEL_DISTORTION_OPERATION_H
#define DISTORTION_BROWN_MODEL_DISTORTION_OPERATION_H

#include "ote/ote_defines.h"

#ifdef __cplusplus
extern "C" {
#endif


void create_distortion_data(ote_grid_mesh *pGridMesh, const uint32_t size_x, const uint32_t size_y);

void update_distortion_data(ote_radial radial, ote_grid_mesh *pGridMesh);

#ifdef __cplusplus
}
#endif


#endif //DISTORTION_BROWN_MODEL_DISTORTION_OPERATION_H
