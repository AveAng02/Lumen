#pragma once

#include "Vec3.h"

namespace lumen
{
    struct Scene
    {
        // Image File
        double aspectRatio;
        int image_width;
        int image_height;
        uint32_t spp; // samples per pixel
        int maxDepth;
        bool normal_pass;
        vec3 camera_center;
        vec3 deltaU, deltaV;
        vec3 pXRef;
        vec3 vpReference;
    };
}