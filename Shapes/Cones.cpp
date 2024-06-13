//
// Created by Jean-Baptiste  Azan on 23/04/2024.
//

#include "Cones.hpp"

namespace Raytracer {
    extern "C"
    {
        std::unique_ptr<IShape> createCones(const vec3 &v, const vec3 &a, double ang, double h, const Color &color) {
            return std::make_unique<Cones>(v, a, ang, h, color);
        }
    }


    bool Cones::hit(const Ray &r, Interval ray_t, double &t_hit, vec3 &hit_normal, Color &hit_color, HitMat &rec) const {
        vec3 oc = r.origin() - vertex;
        double angle_rad = angle * M_PI / 180.0;
        double cos_theta = std::cos(angle_rad);
        double cos_theta_sq = cos_theta * cos_theta;
        double sin_theta_sq = 1.0 - cos_theta_sq;
        double t_min = 0.0;
        double t_max = std::numeric_limits<double>::infinity();
        double A = dot(r.direction(), axis) * dot(r.direction(), axis) - cos_theta_sq;
        double B = 2.0 * (dot(r.direction(), axis) * dot(oc, axis) - dot(r.direction(), oc) * cos_theta_sq);
        double C = dot(oc, axis) * dot(oc, axis) - dot(oc, oc) * cos_theta_sq;

        double discriminant = B * B - 4 * A * C;

        if (discriminant < 0) return false;

        double sqrtd = sqrt(discriminant);
        double root1 = (-B - sqrtd) / (2 * A);
        double root2 = (-B + sqrtd) / (2 * A);

        bool hit_found = false;
        t_hit = std::numeric_limits<double>::infinity();

        std::vector<double> potential_roots = {root1, root2};
        for (double root : potential_roots) {
            if (root < t_min || root > t_max)
                continue;
            vec3 p = r.at(root);
            double h = dot((p - vertex), axis);
            if (h < 0 || h > 1920)
                continue;

            vec3 normal = (p - vertex) - (dot(p - vertex, axis) * axis);
            normal = unit_vector(normal);
            if (dot(normal, r.direction()) > 0) normal = -normal;
            if (root < t_hit) {
                t_hit = root;
                hit_normal = normal;
                hit_color = color;
                hit_found = true;
            }
        }
        return hit_found;
    }
}
