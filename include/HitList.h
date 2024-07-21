#pragma once

#ifndef HITLIST
#define HITLIST

#include "Geometry.h"

#include <memory>
#include <vector>

namespace lumen
{
    class HitList : public Geometry
    {
    public:

        HitList() {}
        HitList(std::shared_ptr<Geometry> object) 
        : objList(std::vector<std::shared_ptr<Geometry>>({object}))
        {}

        bool hit(const ray& r, 
                double ray_tmin, 
                double ray_tmax,
                hitRecord& rec) const override
        {
            hitRecord tempRec;
            bool hasHit = false;
            auto closest = ray_tmax;

            for(const auto& obj : objList)
            {
                if(obj->hit(r, ray_tmin, closest, tempRec))
                {
                    hasHit = true;
                    closest = tempRec.t;
                    rec = tempRec;
                }
            }

            return hasHit;
        }

        void add(std::shared_ptr<Geometry> obj)
        {
            objList.push_back(obj);
        }

        std::vector<std::shared_ptr<Geometry>> objList;
    };
}

#endif