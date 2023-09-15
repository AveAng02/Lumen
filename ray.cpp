#include "vec3.h"
#include "ray.h"

#include <cmath>
#include <iostream>

ray::ray() {}

ray::ray(const point3 origin, const vec3& direction): o(origin), d(direction) {

}

point3 ray::origin() const
{
    return o;
}

vec3 ray::direction() const
{
    return d;
}

point3 ray::at(const double t) const
{
    return o + t*d;
}