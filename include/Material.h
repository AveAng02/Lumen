#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H

#include "Lumen.h"
#include "Geometry.h"
#include "RenderUtils.h"

namespace lumen
{
    class Material
    {
    public:
        Material(const color& col_ = color()) {}

        virtual ~Material() = default;

        virtual bool scatter(const ray& r, const hitRecord& record, 
                            color& attenuation, ray& scatteredRay) const = 0;

        color albedo;
    };

    class Lambertian : public Material
    {
    public:
        Lambertian(const color& albedo_)
        {
            albedo = albedo_;
        }

        virtual bool scatter(const ray& rayIn, const hitRecord& rec, 
            color& attenuation, ray& scattered) const
        {
            auto randVec = randomVec().normalize();

            if(rec.normal.dot(randVec) < 0)
                randVec = -randVec;

            auto scatterDirec = rec.normal + randVec;

            if(nearZero(scatterDirec))
                scatterDirec = rec.normal;

            scattered = ray(rec.p, scatterDirec);
            attenuation = albedo;
            return true;
        }
    };

    class Metal : public Material
    {
    public:
        Metal(const color& albedo_)
        {
            albedo = albedo_;
        }

        virtual bool scatter(const ray& rayIn, const hitRecord& rec, 
            color& attenuation, ray& scattered) const
        {
            auto reflected = getReflectedVec(rayIn.direction(), rec.normal);
            scattered = ray(rec.p, reflected);
            attenuation = albedo;
            return true;
        }
    };
}

#endif // MATERIAL_H
