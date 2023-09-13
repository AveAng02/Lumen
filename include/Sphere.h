#pragma once


#include "Ray.h"


namespace lumen
{
    // SPHERE 
    struct SPHERE
    {
        point3 center;
        double radius;
        color sph_color;
        std::string name;

        SPHERE()
        {
            this->center = point3(0,0,0);
            this->radius = 0.0;
            this->sph_color = color(0,0,0);
            this->name = "SPHERE";
        }

        SPHERE(point3 center_, double radius_, color col_, std::string name_)
        {
            this->center = center_;
            this->radius = radius_;
            this->sph_color = col_;
            this->name = name_;
        }
    };

    double hit_sphere(const SPHERE sp, const ray& r)
    {
        vec3 oc = r.origin() - sp.center;
        auto a = r.direction() * r.direction();
        auto b = 2.0 * oc * r.direction();
        auto c = oc*oc - sp.radius*sp.radius;
        auto D = b*b - 4*a*c;

        return (D > 0)? ((-b - sqrt(D)) / (2.0*a)) : -1 ;
    }
}
