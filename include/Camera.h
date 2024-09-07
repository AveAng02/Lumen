#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#define BEAUTY_PASS
// #define NORMAL_PASS

#include "Lumen.h"
#include "HitList.h"

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
            auto vpReference = camera_center - lumen::vec3(0, 0, focal_length) 
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

            for(int i = 0, j = 0; i < image_height; i++)
            {
                for(j = 0; j < image_width; j++)
                {
                    auto pXCentre = pXRef + (i * deltaU) + (j * deltaV);
                    auto rayDirection = pXCentre - camera_center;
                    hitRay = lumen::ray(pXCentre, rayDirection);

                    pixelCol = lumen::ray_normal_color(hitRay, world);
                    
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
        bool normal_pass;

    private:
        vec3 camera_center;
        vec3 deltaU, deltaV;
        vec3 pXRef;
    };
}

#endif // CAMERA_H