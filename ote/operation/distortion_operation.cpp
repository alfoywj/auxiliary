//
// Created by redbean on 22. 8. 27.
//

#include <valarray>
#include "distortion_operation.h"

void create_distortion_data(ote_grid_mesh *pGridMesh, const uint32_t size_x, const uint32_t size_y) {
    uint32_t vertex_count = (size_x + 1) * (size_y + 1);
    ote_vec4 *vertices = new ote_vec4[vertex_count];
    uint32_t max_index_count = 6 * size_x * size_y;
    uint32_t *indices = new uint32_t[max_index_count];

    for (uint32_t y = 0; y <= size_y; ++y) {
        float yf = (float) y / size_y;
        for (uint32_t x = 0; x <= size_x; ++x) {
            float xf = (float) x / size_x;
            uint32_t index = y * size_x + x;
            vertices[index].x = -1.0f + xf;
            vertices[index].y = -1.0f + yf;
        }
    }

    uint32_t index = 0;
    for (uint32_t y = 0; y < size_y; ++y) {
        for (uint32_t x = 0; x < size_x; ++x) {
            indices[index + 0] = y * (size_x + 1) + x;
            indices[index + 1] = y * (size_x + 1) + x + 1;
            indices[index + 2] = (y + 1) * (size_x + 1) + x + 1;
            indices[index + 3] = y * (size_x + 1) + x;
            indices[index + 4] = (y + 1) * (size_x + 1) + x + 1;
            indices[index + 5] = (y + 1) * (size_x + 1) + x;
            index += 6;
        }
    }
    pGridMesh->size_x = size_x;
    pGridMesh->size_y = size_y;
    pGridMesh->dataMesh.vertex_count = vertex_count;
    pGridMesh->dataMesh.index_count = index;
    pGridMesh->dataMesh.indices = indices;
    pGridMesh->dataMesh.stride = sizeof(ote_vec4) / sizeof(float);
    pGridMesh->dataMesh.vertices = (float *) vertices;// sizeof(float) * vertex_count * stride
}

void update_distortion_data(ote_radial radial, ote_grid_mesh *pGridMesh) {
    const uint32_t size_x = pGridMesh->size_x;
    const uint32_t size_y = pGridMesh->size_y;
    ote_vec4 *vertices = (ote_vec4 *) pGridMesh->dataMesh.vertices;
    for (uint32_t y = 0; y <= size_y; ++y) {
        float yf = (float) y / size_y;
        for (uint32_t x = 0; x <= size_x; ++x) {
            float xf = (float) x / size_x;
            uint32_t index = y * size_x + x;
            float xu = -1.0f + xf;
            float yu = -1.0f + yf;
            float r = sqrt(xu * xu + yu * yu);
            float brown =
                    radial.K[0]
                    + radial.K[1] * r
                    + radial.K[2] * r * r
                    + radial.K[3] * r * r * r
                    + radial.K[4] * r * r * r * r
                    + radial.K[5] * r * r * r * r * r
                    + radial.K[6] * r * r * r * r * r * r;
            vertices[index].x = xu * brown;
            vertices[index].y = -1.0f + yf;
        }
    }
}
