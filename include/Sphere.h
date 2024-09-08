#pragma once

#include "MathUtils.h"
#include "Ray.h"
#include "Geometry.h"
#include "Material.h"

namespace lumen
{
    // SPHERE 
    class Sphere : public Geometry
    {
    public:
        Sphere(point3 center_ = point3(0.0f, 0.0f, 0.0f), 
               double radius_ = 1.0f, 
               color col_ = color(), 
               std::string name_ = "SPHERE")
        :   center(center_),
            radius(radius_),
            name(name_)
        {
            mat->albedo = col_;
        }

        Sphere(std::shared_ptr<Material> mat_,
               point3 center_ = point3(0.0f, 0.0f, 0.0f), 
               double radius_ = 1.0f, 
               std::string name_ = "SPHERE")
        :   center(center_),
            radius(radius_),
            name(name_)
        {
            mat = mat_;
        }

        // Checks if the sphere hits the body
        // Optimised intersection code
        bool hit(const ray& r, 
                double ray_tmin, 
                double ray_tmax,
                hitRecord& rec) const override
        {
            vec3 oc = center - r.origin();
            auto a = r.direction().length_squared();
            auto h = oc.dot(r.direction());
            auto c = oc.length_squared() - radius * radius;
            auto discriminant = h*h - a*c;

            if(discriminant < 0)
                return false;

            auto sqrtd = sqrt(discriminant);

            // Getting nearest root
            // Calculating the first root of the quadratic
            auto root = (h - sqrtd) / a;

            if( root <= ray_tmin || root >= ray_tmax)
            {
                // Calculating the second root of the quadratic
                root = (h + sqrtd) / a;

                if(root <= ray_tmin || root >= ray_tmax)
                    return false;
            }

            // Storing distance of intersection
            rec.t = root;

            // Storing point of intersection
            rec.p = r.at(rec.t);

            // Calculating the normal at the point of intersection
            rec.normal = (rec.p - center) / radius;

            vec3 outNormal = (rec.p - center) / radius;
            rec.setFaceNormal(r, outNormal); // Setting the value of normal
            rec.mat = mat;

            return true;
        }

        point3 center;
        double radius;
        std::string name;
    };
}
