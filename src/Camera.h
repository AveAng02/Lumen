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
            aspectRatio = 16.0 / 9.0;
            image_width = 400u;
            image_height = image_width / aspectRatio;

            // Camera
            // Camera position = (0,0,0)
            auto focal_length = 1.0;
            auto vpW = 2.0;  // view port height
            auto vpH = vpW / aspectRatio; // view port width
            camera_center = lumen::point3(0, 0, 1);

            // Vectors on the view port edges
            auto horizontal = lumen::vec3(vpW, 0, 0); // view port u
            auto vertical = lumen::vec3(0, -vpH, 0);  // view port v

            // Pitch between pixels in horizontal and vertical directions
            deltaU = horizontal / image_width;
            deltaV = vertical / image_height;

            // Location of upper left corner of the view port
            auto vpReference = camera_center - lumen::vec3(0, 0, focal_length) 
                                - horizontal/2 - vertical/2;
            pXRef = vpReference + 0.5 * (deltaU + deltaV); // Location of upper left pixel
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
