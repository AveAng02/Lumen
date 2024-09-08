#pragma once

#ifndef LUMEN
#define LUMEN

#include <limits>

namespace lumen
{
    // Constants
    const double INF = std::numeric_limits<double>::infinity();
    const double PI = 3.1415926535897932385;

    // Utility functions
    inline double degreesToRadians(double degrees)
    {
        return (degrees * PI) / 180.0;
    }
}

#include "Vec3.h"
#include "Scene.h"
#include "Ray.h"
#include "MathUtils.h"
#include "Color.h"
#include "Material.h"
#include "Geometry.h"
#include "HitList.h"
#include "Sphere.h"
#include "Pass.h"
#include "Camera.h"

#endif // LUMEN
