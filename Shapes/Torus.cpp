/*
** EPITECH PROJECT, 2024
** B-OOP-400-LIL-4-1-raytracer-theo.lemaire
** File description:
** Torus.cpp
*/

#include "Torus.hpp"

namespace Raytracer {

    extern "C" {
    std::unique_ptr<IShape> createObject(const point3 &center, double majorRadius, double minorRadius, const Color &color) {
        return std::make_unique<Torus>(center, majorRadius, minorRadius, color);
        }
    }

    bool solveQuadratic(double a, double b, double c, std::vector<double>& roots) {
        double discriminant = b * b - 4 * a * c;
        if (discriminant < 0)
            return false;
        else if (discriminant == 0) {
            roots.push_back(-b / (2 * a));
        } else {
            roots.push_back((-b + sqrt(discriminant)) / (2 * a));
            roots.push_back((-b - sqrt(discriminant)) / (2 * a));
        }
        return true;
    }

    bool solveCubic(double a, double b, double c, double d, std::vector<double>& roots) {
        if (a == 0)
            return solveQuadratic(b, c, d, roots);

        double f = ((3 * c / a) - (b * b / (a * a))) / 3;
        double g = (((2 * b * b * b) / (a * a * a)) - ((9 * b * c) / (a * a)) + (27 * d / a)) / 27;
        double h = (g * g / 4) + (f * f * f / 27);

        if (h > 0)
            return false;

        double i = sqrt((g * g / 4) - h);
        double j = cbrt(i);
        double k = acos(-(g / (2 * i)));
        double m = cos(k / 3);
        double n = sqrt(3.0) * sin(k / 3);
        double p = -(b / (3 * a));

        roots.push_back(2 * j * m + p);
        roots.push_back(-j * (m + n) + p);
        roots.push_back(-j * (m - n) + p);

        return true;
    }

    bool solveQuartic(double a, double b, double c, double d, double e, std::vector<double>& roots) {
        if (a == 0)
            return solveCubic(b, c, d, e, roots);

        double alpha = (-3 * b * b) / (8 * a * a) + (c / a);
        double beta = (b * b * b) / (8 * a * a * a) - (b * c) / (2 * a * a) + (d / a);
        double gamma = (-3 * b * b * b * b) / (256 * a * a * a * a) + (b * b * c) / (16 * a * a * a) - (b * d) / (4 * a * a) + (e / a);

        std::vector<double> cubicRoots;
        if (!solveCubic(1, alpha, (alpha * alpha / 4) - gamma, -(beta * beta / 8), cubicRoots))
            return false;

        double z1 = cubicRoots[0];
        double z2 = cubicRoots[1];
        double z3 = cubicRoots[2];

        roots.push_back(-b / (4 * a) + 0.5 * sqrt(2 * z1 - alpha - 2 * sqrt(z1 * z1 - z1 * alpha + beta)));
        roots.push_back(-b / (4 * a) + 0.5 * sqrt(2 * z1 - alpha + 2 * sqrt(z1 * z1 - z1 * alpha + beta)));
        roots.push_back(-b / (4 * a) + 0.5 * sqrt(2 * z2 - alpha - 2 * sqrt(z2 * z2 - z2 * alpha + beta)));
        roots.push_back(-b / (4 * a) + 0.5 * sqrt(2 * z2 - alpha + 2 * sqrt(z2 * z2 - z2 * alpha + beta)));

        return true;
    }
    bool Torus::hit(const Ray &r, Interval ray_t, double &t_hit, vec3 &hit_normal, Color &hit_color, HitMat &rec) const {
        vec3 origin = r.origin() - center;
        vec3 direction = r.direction();
        double a = direction.length_squared();
        double b = 2 * dot(origin, direction);
        double c = origin.length_squared() + majorRadius * majorRadius - minorRadius * minorRadius;
        double d = 2 * dot(origin, vec3(origin.x(), origin.y(), 0));
        double e = origin.length_squared() - minorRadius * minorRadius;

        // Solve the quartic equation
        std::vector<double> roots;
        if (!solveQuartic(a, b, c, d, e, roots))
            return false;

        // Find the closest intersection point
        t_hit = std::numeric_limits<double>::infinity();
        for (const auto &root : roots) {
            if (root > 0 && root < t_hit) {
                t_hit = root;
            }
        }

        // If no valid intersection found, return false
        if (t_hit == std::numeric_limits<double>::infinity())
            return false;

        // Calculate the intersection point and normal
        point3 intersection_point = r.at(t_hit);
        vec3 torus_normal = intersection_point - center;
        torus_normal = unit_vector(torus_normal);

        // Set the hit normal and color
        hit_normal = torus_normal;
        hit_color = color;

        return true;
    }

}
