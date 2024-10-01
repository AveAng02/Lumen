#pragma once
#include <random>
#include <limits>

#include "Vec3.h"

namespace lumen
{
    // Constants
    const double INF = std::numeric_limits<double>::infinity();
    const double PI = 3.1415926535897932385;
    
    bool withinBounds(float x, float min, float max)
    {
        return min < x && x < max;
    }

    float randomFloatInRange(float min = std::numeric_limits<float>::min(), 
                            float max = std::numeric_limits<float>::max())
    {
        /*
        std::uniform_real_distribution<float> distribution(min, max);
        std::mt19937 generator;
        return distribution(generator);
        */

        float val = std::rand() / (RAND_MAX + 1.0);
        return min + (max-min)*val;
    }

    int randomIntInRange(int min = std::numeric_limits<int>::min(), 
                        int max = std::numeric_limits<int>::max())
    {
        std::uniform_int_distribution<int> distribution(min, max);
        std::mt19937 generator;
        return distribution(generator);
    }

    float degreeToRadians(float degrees)
    {
        return degrees * PI * 0.0055555555f; // divided by 180 = 0.005555
    }

    float clamp(float x, float min, float max)
    {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

    float linearToGamma(float linearComponent)
    {
        if (linearComponent > 0)
            return std::sqrt(linearComponent);

        return 0;
    }

    bool nearZero(vec3 v)
    {
        auto esp = 1e-5;
        return (std::fabs(v[0]) < esp) 
                && (std::fabs(v[1]) < esp) 
                && (std::fabs(v[2]) < esp);
    }
}


