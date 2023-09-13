#pragma once


#include "Vec3.h"


namespace lumen
{
    // Ray Class
    class ray
    {
        public:
            ray() {}

            ray(const point3 origin, const vec3& direction): o(origin), d(direction) {}

            point3 origin() const
            {
                return o;
            }

            vec3 direction() const
            {
                return d;
            }

            point3 at(const double t) const
            {
                return o + t*d;
            }

        public:
            point3 o;
            vec3 d;
    };

}

