#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#define BEAUTY_PASS
// #define NORMAL_PASS

#include <iostream>
#include <iomanip>

#include "Lumen.h"
#include "HitList.h"
#include "MathUtils.h"

namespace lumen
{
    class Camera
    {
    public:
        Camera()
        {
            initialize();
        }
        
        void initialize()
        {
            aspectRatio = 16.0 / 9.0;
            image_width = 400u;
            image_height = image_width / aspectRatio;
            spp = 10;

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
            deltaV = horizontal / image_width;
            deltaU = vertical / image_height;

            // Location of upper left corner of the view port
            vpReference = camera_center - lumen::vec3(0, 0, focal_length) 
                                - horizontal/2 - vertical/2;
            pXRef = vpReference + 0.5 * (deltaU + deltaV); // Location of upper left pixel
        }

        void render(const HitList& world)
        {
            ray hitRay;
            color pixelCol;

#ifdef BEAUTY_PASS
            std::ofstream ofs("../output/output_beauty.ppm", std::ios_base::out | std::ios_base::binary);
#endif // BEAUTY_PASS

#ifdef NORMAL_PASS
            std::ofstream ofs("../output/output_normal.ppm", std::ios_base::out | std::ios_base::binary);
#endif // NORMAL_PASS

            ofs << "P3\n" << image_width << ' ' << image_height << "\n255\n";

            std::cout << std::setprecision(2) << std::fixed;

            for(int i = 0, j = 0; i < image_height; i++)
            {
                std::cout << (i * 100.0f / image_height) << " \% completed" << std::endl;

                for(j = 0; j < image_width; j++)
                {
                    pixelCol = color();

                    for(int sample = 0; sample < spp; sample++)
                    {
                        hitRay = getRandomRay(i, j);
#ifdef BEAUTY_PASS
                        pixelCol += ray_color(hitRay, world, maxDepth);
#endif // BEAUTY_PASS

#ifdef NORMAL_PASS
                        pixelCol += ray_normal_color(hitRay, world);
#endif // NORMAL_PASS
                    }

                    pixelCol /= spp;

                    lumen::write_color(ofs, pixelCol);
                }
            }
        }
        // color ray_color(const ray& r, const HitList& world);
        // color ray_normal_color(const ray& r, const HitList& world);

        // Image File
        double aspectRatio;
        int image_width;
        int image_height;
        uint32_t spp; // samples per pixel
        int maxDepth;
        bool normal_pass;

    private:
        ray getRandomRay(int shifti, int shiftj)
        {
            auto offset = vec3(randomFloatInRange(0.0f, 1.0f), 
                            randomFloatInRange(0.0f, 1.0f), 0);

            auto samplePixel = vpReference
                            + ((shifti + offset[0]) * deltaU)
                            + ((shiftj + offset[1]) * deltaV);

            auto rayOrigin = camera_center;
            auto rayDirection = (samplePixel - camera_center).normalize();
            return ray(rayOrigin, rayDirection);
        }


        vec3 camera_center;
        vec3 deltaU, deltaV;
        vec3 pXRef;
        vec3 vpReference;
    };
}

#endif // CAMERA_H
