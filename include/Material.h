#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H

#include "Lumen.h"

namespace lumen
{
    class hitRecord;

    class Material
    {
    public:

        virtual ~Material() = default;

        virtual bool scatter(const ray& r, const hitRecord& record, 
                            color& attenuation, ray& scatteredRay) const  = 0;

        color matCol;
    };

    class Lambertian : public Material
    {
    public:
        Lambertian(const color& albedo)
        {
            matCol = albedo;
        }

        bool scatter

    };
}

#endif // MATERIAL_H
