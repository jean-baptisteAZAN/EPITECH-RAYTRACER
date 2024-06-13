//
// Created by Jean-Baptiste  Azan on 27/04/2024.
//

#include "Cylinder.hpp"

namespace Raytracer {

    extern "C" {
    std::unique_ptr<IShape>
    createCylinder(const point3 &center, const vec3 &axis, double radius, double height, const Color &color,
                   std::shared_ptr<Material> m, vec3 rotation) {
        return std::make_unique<Cylinder>(center, axis, radius, height, color, m, rotation);
    }
    }

    vec3 Cylinder::rotateY(const vec3 &p, double angle) const {
        double rad = angle * PI / 180.0;
        double cosA = cos(rad);
        double sinA = sin(rad);
        return vec3(p.e[0] * cosA + p.e[2] * sinA, p.e[1], p.e[2] * cosA - p.e[0] * sinA);
    }

    vec3 Cylinder::rotateX(const vec3 &p, double angle) const {
        double rad = angle * PI / 180.0;
        double cosA = cos(rad);
        double sinA = sin(rad);
        return vec3(p.e[0], p.e[1] * cosA - p.e[2] * sinA, p.e[1] * sinA + p.e[2] * cosA);
    }

    vec3 Cylinder::rotateZ(const vec3 &p, double angle) const {
        double rad = angle * PI / 180.0;
        double cosA = cos(rad);
        double sinA = sin(rad);
        return vec3(p.e[0] * cosA - p.e[1] * sinA, p.e[0] * sinA + p.e[1] * cosA, p.e[2]);
    }


    bool Cylinder::hit(const Ray &r, Interval ray_t, double &t_hit, vec3 &hit_normal, Color &hit_color, HitMat &rec) const {
        vec3 rotated_direction = rotateX(rotateY(rotateZ(r.direction(), -rotation.e[2]), -rotation.e[1]),
                                         -rotation.e[0]);
        vec3 rotated_origin = rotateX(rotateY(rotateZ(r.origin(), -rotation.e[2]), -rotation.e[1]), -rotation.e[0]);
        Ray rotated_ray(rotated_origin, rotated_direction);

        vec3 oc = rotated_ray.origin() - center;
        double a = dot(rotated_ray.direction(), rotated_ray.direction()) - pow(dot(rotated_ray.direction(), axis), 2);
        double b = 2.0 * (dot(oc, rotated_ray.direction()) - dot(oc, axis) * dot(rotated_ray.direction(), axis));
        double c = dot(oc, oc) - pow(dot(oc, axis), 2) - radius * radius;
        double discriminant = b * b - 4 * a * c;

        if (discriminant < 0) {
            return false;
        }

        double disc_sqrt = sqrt(discriminant);
        double t0 = (-b - disc_sqrt) / (2.0 * a);
        double t1 = (-b + disc_sqrt) / (2.0 * a);

        double z0 = dot(axis, rotated_ray.at(t0) - center);
        double z1 = dot(axis, rotated_ray.at(t1) - center);

        if (z0 < 0 || z0 > height) {
            if (z1 < 0 || z1 > height) {
                return false;
            } else {
                t_hit = t1;
            }
        } else {
            if (z1 < 0 || z1 > height) {
                t_hit = t0;
            } else {
                t_hit = t0 < t1 ? t0 : t1;
            }
        }

        if (t_hit < ray_t.minimum || t_hit > ray_t.maximum) {
            return false;
        }

        vec3 p = rotated_ray.at(t_hit);
        vec3 outward_normal = (p - center) - dot((p - center), axis) * axis;
        hit_normal = unit_vector(outward_normal);
        hit_color = color;
        rec.p = r.at(t_hit);
        rec.normal = hit_normal;
        rec.mat_ptr = mat;

        return true;
    }
}
