#pragma once

#ifndef CAMERA_H__
#define CAMERA_H__

#include <memory>

#include "MathUtils.h"
#include "Vec3.h"

namespace lumen
{
    class Camera
    {
    public:
        Camera() {}
        
        void initialize()
        {
            image_height = image_width / aspectRatio;

            camera_center = lookFrom;

            auto focal_length = (lookFrom - lookAt).length();
            auto theta = degreeToRadians(vfov);
            auto h = std::tan(theta / 2.0f);
            auto vpH = 2.0f * h * focal_length;
            auto vpW = vpH * aspectRatio;

            w = (lookFrom - lookAt).normalize();
            u = vup.cross(w).normalize();
            v = w.cross(u);

            auto vpU = vpW * u;
            auto vpV = vpH * -v;

            deltaU = vpU / image_width;
            deltaV = vpV / image_height;

            auto vpUpLeft = camera_center - (focal_length * w) - vpU/2 - vpV/2;

            pXRef = vpUpLeft + 0.5 * (deltaU + deltaV);
        }

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
