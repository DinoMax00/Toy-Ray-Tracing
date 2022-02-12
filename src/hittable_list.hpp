#pragma once


#include <memory>
#include <vector>

#include "hittable.h"

using std::shared_ptr;
using std::make_shared;

/// to store a list of hittable objects 

class hittable_list: public hittable {

public:
    std::vector<shared_ptr<hittable> > objects;

    hittable_list() {}
    hittable_list(shared_ptr<hittable> obj) { add(obj); }

    void add(shared_ptr<hittable> obj) { objects.push_back(obj); }
    void clear() { objects.clear(); }

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
};


bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    double closest_position = t_max;

    for (const auto& obj: objects) {
        if (obj->hit(r, t_min, closest_position, temp_rec)) {
            hit_anything = true;
            closest_position = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}