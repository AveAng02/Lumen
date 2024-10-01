#pragma once

#ifndef CAMERA_H__
#define CAMERA_H__

#include <memory>

#include "Vec3.h"

namespace lumen
{
    class Camera
    {
    public:
        Camera() {}
        
        void initialize();

        double aspectRatio;
        int image_width;
        int image_height;
        uint32_t spp; // samples per pixel
        int maxDepth;
        bool normal_pass;
        vec3 camera_center;
        vec3 deltaU, deltaV;
        vec3 pXRef;
        point3 lookFrom, lookAt;
        vec3 vup;
        float vfov;
        vec3 u, v, w;
    };
}

#endif // CAMERA_H
