#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <iomanip>
#include <memory>
#include <thread>

#include "Lumen.h"
#include "Scene.h"
#include "HitList.h"
#include "MathUtils.h"
#include "RenderUtils.h"
#include "Integrator.h"

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
            globalCounter = 0;
            
            scene.aspectRatio = 16.0 / 9.0;
            scene.image_width = 800u;
            scene.image_height = scene.image_width / scene.aspectRatio;
            scene.spp = 10;

            // Camera
            // Camera position = (0,0,0)
            auto focal_length = 1.0;
            auto vpW = 2.0;  // view port height
            auto vpH = vpW / scene.aspectRatio; // view port width
            scene.camera_center = lumen::point3(0, 0, 1);

            // Vectors on the view port edges
            auto horizontal = lumen::vec3(vpW, 0, 0); // view port u
            auto vertical = lumen::vec3(0, -vpH, 0);  // view port v

            // Pitch between pixels in horizontal and vertical directions
            scene.deltaV = horizontal / scene.image_width;
            scene.deltaU = vertical / scene.image_height;

            // Location of upper left corner of the view port
            scene.vpReference = scene.camera_center - lumen::vec3(0, 0, focal_length) 
                                - horizontal/2 - vertical/2;
            scene.pXRef = scene.vpReference + 0.5 * (scene.deltaU + scene.deltaV); // Location of upper left pixel
        }

        void render(const HitList& world)
        {
            uint32_t r, g, b;
            ray hitRay;
            color pixelCol;

            // stores the rgb data width wise
            std::vector<uint32_t> rgbData (scene.image_height * scene.image_width * 3, 0); 
            uint32_t c = 0;
            uint32_t totalThreads = 15;
            uint32_t numOfThreads = totalThreads - 1;

            std::cout << "Enter the number of Threads : ";
            std::cin >> totalThreads;
            numOfThreads = totalThreads - 1;

            uint32_t scanLinesPerThread = (scene.image_height / numOfThreads) - 1;
            std::vector<std::thread> threadList (totalThreads);
            std::vector<uint32_t> lowerLimits (numOfThreads, 0), upperLimits (numOfThreads, 0);

            // Defining upper and lower limits
            lowerLimits[0] = 0;
            upperLimits[numOfThreads - 1] = scene.image_height - 1;

            for(int i = 0; i < numOfThreads - 1; i++)
            {
                upperLimits[i] = lowerLimits[i] + scanLinesPerThread;
                lowerLimits[i + 1] = upperLimits[i] + 1;
            }

            // Creating data per thread
            std::vector<std::vector<uint32_t>> rgbDataPerThread (numOfThreads);

            for(int i = 0; i < numOfThreads; i++)
            {
                rgbDataPerThread[i] = std::vector<uint32_t>
                                ((upperLimits[i] - lowerLimits[i] + 1) * scene.image_width * 3, 0);
            }

            // creating threads
            for(int i = 0; i < numOfThreads; i++)
            {
                threadList[i] = std::thread(integratorKernel, std::ref(rgbDataPerThread[i]), 
                                scene, world, i, lowerLimits[i], upperLimits[i]);
            }

            // initializing the counter thread
            threadList[totalThreads - 1] = std::thread(counter, totalThreads - 1, scene.image_height);

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

            ofs << "P3\n" << scene.image_width << " " << scene.image_height << "\n255\n";

            for(int i = 0, j = 0; i < rgbDataPerThread.size(); i++)
            {
                for(j = 0; j < rgbDataPerThread[i].size(); j+=3)
                {
                    ofs << rgbDataPerThread[i][j] << " " << rgbDataPerThread[i][j+1] 
                    << " " << rgbDataPerThread[i][j+2] << "\n";
                }
            }
        }
        

        ray getRandomRay(int shifti, int shiftj) const 
        {
            auto offset = vec3(randomFloatInRange(0.0f, 1.0f), 
                            randomFloatInRange(0.0f, 1.0f), 0);

            auto samplePixel = scene.vpReference
                            + ((shifti + offset[0]) * scene.deltaU)
                            + ((shiftj + offset[1]) * scene.deltaV);

            auto rayOrigin = scene.camera_center;
            auto rayDirection = (samplePixel - scene.camera_center).normalize();
            return ray(rayOrigin, rayDirection);
        }
        

        // Scene Definition
        Scene scene;
    };
}

#endif // CAMERA_H
