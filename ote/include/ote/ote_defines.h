//
// Created by redbean on 22. 8. 24.
//

#ifndef DISTORTION_BROWN_MODEL_DBM_DEFINES_H
#define DISTORTION_BROWN_MODEL_DBM_DEFINES_H

#include <stdint.h>
#include <vector>
#ifdef __cplusplus
extern "C" {
#endif

struct ote_vec2 {
    float x;
    float y;
};

struct ote_vec3 {
    float x;
    float y;
    float z;
};

struct ote_vec4 {
    union {
        float x;
        float r;
    };
    union {
        float y;
        float g;
    };
    union {
        float z;
        float b;
        float u;
    };
    union {
        float w;
        float a;
        float v;
    };
};

struct ote_radial {
    float K[7];
};

struct ote_data_mesh {
    //! Data.
    float *vertices;
    //! Number of vertices.
    uint32_t vertex_count;
    //! Stride of vertices
    uint32_t stride;
    //! Indices, for triangle strip.
    uint32_t *indices;
    //! Number of indices for the triangle strips (one per view).
    uint32_t index_count;
};

struct ote_grid_mesh {
    uint32_t size_x;
    uint32_t size_y;
    ote_data_mesh dataMesh;
};

#ifdef __cplusplus
}
#endif

#endif //DISTORTION_BROWN_MODEL_DBM_DEFINES_H
