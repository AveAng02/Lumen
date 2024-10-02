#pragma once

#ifndef MATERIAL_H__
#define MATERIAL_H__

#include "Geometry.h"
#include "RenderUtils.h"
#include "Geometry.h"

namespace lumen
{
    class Material
    {
    public:
        enum class MatType
        {
            LAMBERTIAN,
            DIELECTRIC,
            METAL
        };

        Material(const color& col_ = color()) {}

        virtual ~Material() = default;

        virtual bool scatter(const ray& r, const hitRecord& record, 
                            color& attenuation, ray& scatteredRay) const = 0;

        virtual void print() const = 0;

        color albedo;
        MatType type;
    };

    class Lambertian : public Material
    {
    public:
        Lambertian(const color& albedo_)
        {
            albedo = albedo_;
            type = Material::MatType::LAMBERTIAN;
        }

        virtual void print() const override
        {
            std::cout << "Lambertian" << std::endl; 
        }

        virtual bool scatter(const ray& rayIn, const hitRecord& rec, 
            color& attenuation, ray& scattered) const
        {
            auto randVec = randomVecInUnitSphere().normalize();

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
        Metal(const color& albedo_, float fuzz)
        : metalFuzz(fuzz)
        {
            albedo = albedo_;
            type = Material::MatType::METAL;
        }

        virtual void print() const override
        {
            std::cout << "Metal" << std::endl; 
        }

        virtual bool scatter(const ray& rayIn, const hitRecord& rec, 
            color& attenuation, ray& scattered) const
        {
            auto reflected = getReflectedVec(rayIn.direction(), rec.normal);
            reflected = reflected.normalize() 
                        + (metalFuzz * randomVecInUnitSphere().normalize());
            scattered = ray(rec.p, reflected);
            attenuation = albedo;
            return (scattered.direction().dot(rec.normal) > 0.0f);
        }

    private:
        float metalFuzz;
    };

    class Dielectric : public Material
    {
    public:
        Dielectric(float ri)
        : refractiveIndex(ri)
        {
            type = Material::MatType::DIELECTRIC;
        }

        virtual void print() const override
        {
            std::cout << "Dielectric" << std::endl; 
        }

        virtual bool scatter(const ray& inRay, const hitRecord& rec, 
            color& attenuation, ray& scattered) const
        {
            attenuation = color(1.0f, 1.0f, 1.0f);

            vec3 unitDirec = inRay.direction().normalize();
            vec3 nextRay;
            float rx = rec.geoFaceFront ? (1.0f / refractiveIndex) : refractiveIndex;
            float cosTheta = std::fmin(rec.normal.dot(-unitDirec), 1.0f);
            float sinTheta = std::sqrt(1.0f - cosTheta * cosTheta);            

            if(rx * sinTheta > 1.0f 
              || reflectance(cosTheta, rx) > randomFloatInRange(0, 1))
            {
                nextRay = getReflectedVec(unitDirec, rec.normal);
            }
            else
            {
                nextRay = getRefractedVec(unitDirec, rec.normal, rx);
            }
        
            scattered = ray(rec.p, nextRay);
            return true;
        }

    private:
        float refractiveIndex;
    };

    void hitRecord::print()
    {
        std::cout << "Depth = " << depth << std::endl;
        std::cout << "hitpoint = ";
        p.print();
        std::cout << "normal at hitpoint = ";
        normal.print();
        std::cout << "color found = ";
        hitCol.print();
        std::cout << "Ray traversing :";
        r.print();
        std::cout << "Material Type : ";
        mat->print();
    }
}

#endif // MATERIAL_H__
