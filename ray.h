#include "vec3.h"

#include <cmath>
#include <iostream>

// Ray Class

class ray
{
    public:
        ray();

        ray(const point3 origin, const vec3& direction);

        point3 origin() const;

        vec3 direction() const;

        point3 at(const double t) const;

    public:
        point3 o;
        vec3 d;
};

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