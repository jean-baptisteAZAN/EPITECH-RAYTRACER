//
// Created by Jean-Baptiste  Azan on 24/04/2024.
//

#include "Plane.hpp"

namespace Raytracer {
    extern "C"
    {
        std::unique_ptr<IShape> createObject(const point3 &position, const vec3 &normal, double size, const Color &color, std::shared_ptr<Material> mat) {
            return std::make_unique<Plane>(position, normal, size, color, mat);
        }
    }

    bool Plane::hit(const Ray &r, Interval ray_t, double &t_hit, vec3 &hit_normal, Color &hit_color, HitMat &rec) const {
        double denom = dot(normal, r.direction());
        if (fabs(denom) > 1e-6) {
            double t = dot(position - r.origin(), normal) / denom;
            if (t >= 0) {
                vec3 hit_point = r.origin() + t * r.direction();
                if (fabs(hit_point.e[0] - position.e[0]) > size / 2 ||
                    fabs(hit_point.e[1] - position.e[1]) > size / 2 ||
                    fabs(hit_point.e[2] - position.e[2]) > size / 2) {
                    return false;
                }
                t_hit = t;
                hit_normal = normal;
                hit_color = color;
                return true;
            }
        }
        return false;
    }
}
