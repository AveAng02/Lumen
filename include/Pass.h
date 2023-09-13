#pragma once

#include "Vec3.h"
#include "Ray.h"
#include "Sphere.h"


namespace lumen
{
    // Defining Ray Color
    color ray_color(const ray& r, SPHERE sp)
    {
        if(hit_sphere(sp, r) >= 0.0)
        {
            return sp.sph_color;
        }

        vec3 unit_direc = unit(r.direction());

        auto t = 0.5 * (unit_direc.y() + 1.0);

        return (1.0 - t)*color(1,1,1) + t*color(0.5,0.7,1);
    }


    // Normal
    color ray_normal_color(const ray& r, SPHERE sp)
    {
        auto t = hit_sphere(sp, r);
        
        if(t > 0.0)
        {
            vec3 normal = unit(r.at(t) - sp.center);
            return 0.5*color(normal.x() + 1, normal.y() + 1, normal.z() + 1);
        }

        vec3 unit_direc = unit(r.direction());

        t = 0.5 * (unit_direc.y() + 1.0);

        return (1.0 - t)*color(1,1,1) + t*color(0.5,0.7,1);
    }
}


