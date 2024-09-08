#pragma once

#include <vector>
#include <string>

#include "Ray.h"
#include "Camera.h"
#include "MathUtils.h"

namespace lumen
{
    void integratorKernel(std::vector<uint32_t>& rgbData, 
                        const Camera& cam,
                        const HitList& world,
                        const int scanLineBegin, 
                        const int scanLineEnd)
    {
        ray hitRay;
        color pixelCol;
        int c = scanLineBegin * cam.image_width * 3;
        int cEnd = scanLineEnd * cam.image_width * 3;

        std::cout << std::setprecision(2) << std::fixed;

        for(int i = scanLineBegin, j = 0; i < scanLineEnd; i++)
        {
            std::cout << (i * 100.0f / cam.image_height) << " \% completed" << std::endl;

            for(j = 0; j < cam.image_width; j++)
            {
                pixelCol = color();

                for(int sample = 0; sample < cam.spp; sample++)
                {
                    hitRay = cam.getRandomRay(i, j);
#ifdef BEAUTY_PASS
                    pixelCol += ray_color(hitRay, world, cam.maxDepth);
#endif // BEAUTY_PASS

#ifdef NORMAL_PASS
                    pixelCol += ray_normal_color(hitRay, world);
#endif // NORMAL_PASS
                }

                pixelCol /= cam.spp;

                rgbData[c++] = static_cast<int>(255.999 * clamp(pixelCol[0], 0.0f, 1.0f));
                rgbData[c++] = static_cast<int>(255.999 * clamp(pixelCol[1], 0.0f, 1.0f));
                rgbData[c++] = static_cast<int>(255.999 * clamp(pixelCol[2], 0.0f, 1.0f));
            }

            if(c >= cEnd)
            {
                break;
            }
        }
    }
}

