//
// Created by Jean-Baptiste  Azan on 27/04/2024.
//

#include "Triangle.hpp"

namespace Raytracer {

    extern "C" {
    std::unique_ptr<IShape> createObject(const point3 &v0, const point3 &v1, const point3 &v2, const Color &color,
                                         std::shared_ptr<Material> mat_ptr) {
        return std::make_unique<Triangle>(v0, v1, v2, color, mat_ptr);
    }
    }


    bool
    Triangle::hit(const Ray &r, Interval ray_t, double &t_hit, vec3 &hit_normal, Color &hit_color, HitMat &rec) const {
        const float EPSILON = 0.0000001;
        vec3 edge1, edge2, h, s, q;
        float a, f, u, v;
        edge1 = v1 - v0;
        edge2 = v2 - v0;
        h = cross(r.direction(), edge2);
        a = dot(edge1, h);
        if (a > -EPSILON && a < EPSILON)
            return false;
        f = 1.0 / a;
        s = r.origin() - v0;
        u = f * dot(s, h);
        if (u < 0.0 || u > 1.0)
            return false;
        q = cross(s, edge1);
        v = f * dot(r.direction(), q);
        if (v < 0.0 || u + v > 1.0)
            return false;
        float t = f * dot(edge2, q);
        if (t > EPSILON) {
            t_hit = t;
            vec3 normal = cross(edge1, edge2);
            float length = sqrt(normal.x() * normal.x() + normal.y() * normal.y() +
                                normal.z() * normal.z());
            if (length > 0) {
                hit_normal = vec3(normal.x() / length, normal.y() / length,
                                  normal.z() / length);
            }
            hit_color = color;
            rec.p = r.at(t_hit);
            rec.normal = hit_normal;
            rec.mat_ptr = mat_ptr;
            return true;
        } else
            return false;
    }

}
