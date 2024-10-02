#pragma once

#include <memory>

#include "Vec3.h"
#include "Ray.h"

namespace lumen
{
    class Material;
    class Geometry;

    class hitRecord
    {
    public:
        int depth;
        ray r;
        point3 p;
        vec3 normal;
        color hitCol;
        double t;
        bool geoFaceFront;
        std::shared_ptr<Material> mat;
        std::shared_ptr<Geometry> geoPtr;

        void setFaceNormal(const ray& r, const vec3& outWardNormal)
        {
            // Set's the hit record normal vector
            geoFaceFront = (outWardNormal.dot(r.direction()) < 0.0f);
            normal = geoFaceFront ? outWardNormal : -outWardNormal;
        }

        void print();
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
        std::shared_ptr<Material> mat;
    };
}
