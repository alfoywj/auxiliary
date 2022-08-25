//
// Created by redbean on 22. 8. 24.
//

#ifndef DISTORTION_BROWN_MODEL_DBM_DEFINES_H
#define DISTORTION_BROWN_MODEL_DBM_DEFINES_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct dbm_vec2 {
    float x;
    float y;
};

struct dbm_vec3 {
    float x;
    float y;
    float z;
};

struct dbm_vec4 {
    float x;
    float y;
    float z;
    float w;
};

struct dbm_radial {
    float K[7];
};

struct {
    //! Data.
    float *vertices;
    //! Number of vertices.
    uint32_t vertex_count;
    //! Stride of vertices
    uint32_t stride;
    //! Indices, for triangle strip.
    int *indices;
    //! Number of indices for the triangle strips (one per view).
    uint32_t index_count;
} Mesh;

#ifdef __cplusplus
}
#endif

#endif //DISTORTION_BROWN_MODEL_DBM_DEFINES_H
