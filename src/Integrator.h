#pragma once

#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include <string>
#include <atomic>
#include <mutex>
#include <thread>

#include "MathUtils.h"
#include "RenderUtils.h"
#include "HitList.h"
#include "Camera.h"
#include "Pass.h"

#define BEAUTY_PASS
// #define NORMAL_PASS

std::atomic_uint32_t globalCounter;
std::mutex mtx;

namespace lumen
{
    void integratorKernel(std::vector<uint32_t>& rgbData, 
                        const Camera& scene,
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
                std::cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b"
                << (globalCounter * 100.0f / height) 
                << " \% completed" << std::flush;

                prev = globalCounter;
            }            
        }

        std::cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b"
        << "100.00 \% completed" << std::endl;
    }

    void render(const HitList& world, const Camera& cam)
    {
        uint32_t r, g, b;
        ray hitRay;
        color pixelCol;

        // stores the rgb data width wise
        std::vector<uint32_t> rgbData (cam.image_height * cam.image_width * 3.0f, 0); 
        uint32_t c = 0;
        uint32_t totalThreads = 15;
        uint32_t numOfThreads = totalThreads - 1;

        std::cout << "Enter the number of Threads : ";
        std::cin >> totalThreads;
        numOfThreads = totalThreads - 1;

        uint32_t scanLinesPerThread = (cam.image_height / numOfThreads) - 1;
        std::vector<std::thread> threadList (totalThreads);
        std::vector<uint32_t> lowerLimits (numOfThreads, 0), upperLimits (numOfThreads, 0);

        // Defining upper and lower limits
        lowerLimits[0] = 0;
        upperLimits[numOfThreads - 1] = cam.image_height - 1;

        for(int i = 0; i < numOfThreads - 1; i++)
        {
            upperLimits[i] = lowerLimits[i] + scanLinesPerThread;
            lowerLimits[i + 1] = upperLimits[i] + 1;
        }

        // Creating data per thread
        std::vector<std::vector<uint32_t>> rgbDataPerThread (numOfThreads);

        for(int i = 0; i < numOfThreads; i++)
        {
            rgbDataPerThread[i] = std::vector<uint32_t>((upperLimits[i] 
                            - lowerLimits[i] + 1) * cam.image_width * 3, 0);
        }

        // creating threads
        for(int i = 0; i < numOfThreads; i++)
        {
            threadList[i] = std::thread(integratorKernel, std::ref(rgbDataPerThread[i]), cam, world, i, lowerLimits[i], upperLimits[i]);
        }

        // initializing the counter thread
        threadList[totalThreads - 1] = std::thread(counter, totalThreads - 1, cam.image_height);

        // joining threads
        for(uint32_t i = 0; i < totalThreads; i++)
        {
            threadList[i].join();
        }

        // Writting data to ppm file
        std::cout << "Writing Data" << std::endl;

#ifdef BEAUTY_PASS
        std::ofstream ofs("../output/output_beauty.ppm", std::ios_base::out | std::ios_base::binary);
#endif // BEAUTY_PASS

#ifdef NORMAL_PASS
        std::ofstream ofs("../output/output_normal.ppm", std::ios_base::out | std::ios_base::binary);
#endif // NORMAL_PASS

        ofs << "P3\n" << cam.image_width << " " << cam.image_height << "\n255\n";

        for(int i = 0, j = 0; i < rgbDataPerThread.size(); i++)
        {
            for(j = 0; j < rgbDataPerThread[i].size(); j+=3)
            {
                ofs << rgbDataPerThread[i][j] << " " << rgbDataPerThread[i][j+1] 
                << " " << rgbDataPerThread[i][j+2] << "\n";
            }
        }
    }
}

