#pragma once

#include "Camera.h"

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
    
    ray getRandomRay(int shifti, int shiftj, const Camera& scene) 
    {
        auto offset = vec3(randomFloatInRange(0.0f, 1.0f), 
                    randomFloatInRange(0.0f, 1.0f), 0);

        auto samplePixel = scene.pXRef
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

    vec3 getRefractedVec(const vec3& direction, const vec3& normal, float nbyn)
    {
        auto cosTheta = std::fmin(normal.dot(-direction), 1.0f);
        vec3 perpendicularVec = nbyn * (direction + cosTheta * normal);
        vec3 parallelVec = -std::sqrt(std::fabs(1.0f 
                            - perpendicularVec.length_squared())) * normal;
        
        return perpendicularVec + parallelVec;
    }

    float reflectance(float cosValue, float refIdx)
    {
        auto r0 = (1.0f - refIdx) / (1.0f + refIdx);
        r0 = r0 * r0;
        return r0 + (1.0f - r0) * std::pow((1.0f - cosValue), 5.0f);
    }
}
