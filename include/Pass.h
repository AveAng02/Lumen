#pragma once

#include "Vec3.h"
#include "Ray.h"
#include "Sphere.h"

namespace lumen
{
    // Defining Ray Color
    color ray_color(const ray& r, const HitList& world)
    {
        hitRecord rec;

        if(world.hit(r, 0, INF, rec))
        {
            // std::cout << "Hit Ball" << std::endl;
            return rec.geoPtr->geoColor;
        }

        vec3 unit_direc = unit(r.direction());
        auto t = 0.5 * (unit_direc.y() + 1.0);
        return (1.0 - t) * color(1,1,1) + t*color(0.5,0.7,1);
    }


    // Normal
    color ray_normal_color(const ray& r, const HitList& world)
    {
        hitRecord rec;

        if(world.hit(r, 0, INF, rec))
        {
            return 0.5 * (rec.normal + color(1, 1, 1));
        }

        vec3 unit_direc = unit(r.direction());
        auto t = 0.5 * (unit_direc.y() + 1.0);
        return (1.0 - t)*color(1,1,1) + t*color(0.5,0.7,1);
    }
}


