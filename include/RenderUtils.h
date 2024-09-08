#pragma once
#include "Ray.h"
#include "Scene.h"
#include "MathUtils.h"

namespace lumen
{
    vec3 randomVec()
    {
        vec3 vec(randomFloatInRange(-1.0f, 1.0f), 
                randomFloatInRange(-1.0f, 1.0f), 
                randomFloatInRange(-1.0f, 1.0f));

        return vec;
    }

    vec3 randomVecInUnitSphere()
    {
        while(true)
        {
            auto p = randomVec();

            if(p.length_squared() < 1.0f)
                return p;
        }
    }
    
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

    vec3 getReflectedVec(const vec3& v, const vec3& n)
    {
        return v - 2 * v.dot(n) * n;
    }
}
