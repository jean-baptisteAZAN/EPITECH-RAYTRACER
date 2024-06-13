//
// Created by Jean-Baptiste  Azan on 23/04/2024.
//

#include "Sphere.hpp"

namespace Raytracer {

    extern "C"
    {
        std::unique_ptr<IShape> createObject(const point3 &center, double radius, const Color &color, std::shared_ptr<Material> m) {
            return std::make_unique<Sphere>(center, radius, color, m);
        }
    }


    bool Sphere::hit(const Ray &r, Interval ray_t, double &t_hit, vec3 &hit_normal, Color &hit_color, HitMat &rec) const {
        vec3 oc = center - r.origin();
        auto a = dot(r.direction(), r.direction());
        auto b = -2.0 * dot(r.direction(), oc);
        auto c = dot(oc, oc) - radius * radius;
        auto discriminant = b * b - 4 * a * c;

        if (discriminant < 0) {
            return false;
        } else {
            t_hit = (-b - sqrt(discriminant)) / (2.0 * a);
            hit_normal = unit_vector(r.at(t_hit) - center);
            hit_color = color;
            rec.p = r.at(t_hit);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            hit_normal = rec.normal;
            hit_color = color;
            rec.mat_ptr = mat;

            return true;
        }
    }

}
