#pragma once
#include <random>
#include <limits>

namespace lumen
{
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

       float num = std::rand() / RAND_MAX;
       return min + (max - min) * num;
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
}


