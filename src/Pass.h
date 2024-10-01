#pragma once

#include "Material.h"

namespace lumen
{
    // Defining Ray Color
    color ray_color(const ray& r, const HitList& world, int depth)
    {
        hitRecord rec;

        if(world.hit(r, 0.001f, INF, rec))
        {
            if(depth <= 0)
            {
                return rec.geoPtr->geoColor;
            }

            ray scattered;
            color attenuation;

            if(rec.mat->scatter(r, rec, attenuation, scattered))
            {
                return attenuation * ray_color(scattered, world, depth - 1);
            }
            return color(0,0,0);
        }

        vec3 unit_direc = r.direction().normalize();
        auto t = 0.5 * (unit_direc.y() + 1.0);
        return (1.0 - t) * color(1,1,1) + t * color(0.5,0.7,1);
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


