#pragma once

#ifndef RAY_H__
#define RAY_H__

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

            void print()
            {
                std::cout << "Ray :\nOrigin : ";
                o.print();
                std::cout << "Direction : ";
                d.print();
            }

        public:
            point3 o;
            vec3 d;
    };

}

#endif // RAY_H__
