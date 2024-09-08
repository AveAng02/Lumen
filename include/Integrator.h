#pragma once

#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include <string>

#include "Ray.h"
#include "Scene.h"
#include "HitList.h"
#include "RenderUtils.h"
#include "MathUtils.h"
#include "Pass.h"

#define BEAUTY_PASS
// #define NORMAL_PASS

namespace lumen
{
    void integratorKernel(std::vector<uint32_t>& rgbData, 
                        const Scene& scene,
                        const HitList& world,
                        int id,
                        const int scanLineBegin, 
                        const int scanLineEnd)
    {
        std::cout << "Starting thread ID " << id << std::endl;

        ray hitRay;
        color pixelCol;
        int c = 0;

        std::cout << std::setprecision(2) << std::fixed;

        for(int i = scanLineBegin, j = 0; i <= scanLineEnd; i++)
        {
            std::cout << (i * 100.0f / scene.image_height) << " \% completed" << std::endl;

            for(j = 0; j < scene.image_width; j++)
            {
                pixelCol = color();

                for(int sample = 0; sample < scene.spp; sample++)
                {
                    hitRay = getRandomRay(i, j, scene);
#ifdef BEAUTY_PASS
                    pixelCol += ray_color(hitRay, world, scene.maxDepth);
#endif // BEAUTY_PASS

#ifdef NORMAL_PASS
                    pixelCol += ray_normal_color(hitRay, world);
#endif // NORMAL_PASS
                }

                pixelCol /= scene.spp;

                rgbData[c++] = static_cast<int>(255.999 * clamp(pixelCol[0], 0.0f, 1.0f));
                rgbData[c++] = static_cast<int>(255.999 * clamp(pixelCol[1], 0.0f, 1.0f));
                rgbData[c++] = static_cast<int>(255.999 * clamp(pixelCol[2], 0.0f, 1.0f));

                // std::cout << rgbData[c - 3] << " " << rgbData[c - 2] << " " << rgbData[c - 1] << std::endl;
            }
        }
    }
}

