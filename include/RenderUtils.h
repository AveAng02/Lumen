
#include "Ray.h"
#include "Scene.h"
#include "MathUtils.h"

namespace lumen
{
    ray getRandomRay(int shifti, int shiftj, const Scene& scene) 
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
}
