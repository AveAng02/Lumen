#pragma once

#include <memory>

#include "Ray.h"

namespace lumen
{
    class Geometry;

    class hitRecord
    {
    public:
        point3 p;
        vec3 normal;
        double t;
        bool geoFaceFront;
        std::shared_ptr<Geometry> geoPtr;
        // TODO: add geometry

        void setFaceNormal(const ray& r, const vec3& outWardNormal)
        {
            // Set's the hit record normal vector
            geoFaceFront = (outWardNormal.dot(r.direction()) < 0.0f);
            normal = geoFaceFront ? outWardNormal : -outWardNormal;
        }
    };

    class Geometry
    {
    public:
        virtual ~Geometry() = default;

        virtual bool hit(const ray& r,
                        double ray_tmin,
                        double ray_tmax,
                        hitRecord& rec) const = 0;

        color geoColor; // TODO: convert to a material pointer
    };
}
