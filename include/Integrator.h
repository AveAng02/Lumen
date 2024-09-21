#pragma once

#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include <string>
#include <atomic>
#include <mutex>

#include "Ray.h"
#include "Scene.h"
#include "HitList.h"
#include "RenderUtils.h"
#include "MathUtils.h"
#include "Pass.h"

#define BEAUTY_PASS
// #define NORMAL_PASS

std::atomic_uint32_t globalCounter;
std::mutex mtx;

namespace lumen
{
    void integratorKernel(std::vector<uint32_t>& rgbData, 
                        const Scene& scene,
                        const HitList& world,
                        int id,
                        const int scanLineBegin, 
                        const int scanLineEnd)
    {
        std::unique_lock<std::mutex> kernelMtx(mtx);
        kernelMtx.unlock();

        ray hitRay;
        color pixelCol;
        int c = 0;

        // std::cout << "Starting thread ID " << id << std::endl;

        for(int i = scanLineBegin, j = 0; i <= scanLineEnd; i++)
        {
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
        
            globalCounter++;
        }
    }

    void counter(int id, int height)
    {
        float prev = 0.0f;

        // std::cout << "Counter thread " << id << " started" << std::endl;
        std::cout << std::setprecision(2) << std::fixed;

        while(std::fabs(globalCounter - height) > 0.1f)
        {
            if(std::fabs(globalCounter - prev) > 0.1f)
            {
                std::cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b"
                << (globalCounter * 100.0f / height) 
                << " \% completed" << std::flush;

                prev = globalCounter;
            }            
        }

        std::cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b"
        << "100.00 \% completed" << std::endl;
    }
}

