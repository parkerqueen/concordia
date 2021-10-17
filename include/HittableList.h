#ifndef HITTABLELIST_H_
#define HITTABLELIST_H_

#include <memory>
#include <vector>
#include <algorithm>

#include "Ray.h"
#include "Hittable.h"

class HittableList : public Hittable {
  public:
    std::vector<std::shared_ptr<Hittable>> objects;

  public:
    HittableList() {}
    HittableList(std::shared_ptr<Hittable> object) { add(object); }

    constexpr void clear() { objects.clear(); }
    void add(std::shared_ptr<Hittable> object) { objects.push_back(object); }

    bool hit(const Ray& ray, const double t_min, const double t_max,
             HitRecord& hit_record) const override {
        HitRecord temp;
        bool hit_anything = false;
        double closest_so_far = t_max;

        std::for_each(objects.begin(), objects.end(), [&](const auto& object) {
            if (object->hit(ray, t_min, closest_so_far, temp)) {
                hit_record = temp;
                hit_anything = true;
                closest_so_far = temp.ray_t;
            }
        });

        return hit_anything;
    }
};

#endif