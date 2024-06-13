//
// Created by Jean-Baptiste  Azan on 30/04/2024.
//

#ifndef B_OOP_400_LIL_4_1_RAYTRACER_THEO_LEMAIRE_TORUS_HPP
#define B_OOP_400_LIL_4_1_RAYTRACER_THEO_LEMAIRE_TORUS_HPP

#include "../include/IShape.hpp"
#include "../include/Color.hpp"
#include "../include/Ray.hpp"
#include <memory>
#include <vector>
#include <cmath>

namespace Raytracer {
    class Torus : public IShape {
    private:
        point3 center;
        double majorRadius;
        double minorRadius;
        Color color;

    public:
        Torus(const point3 &center, double majorRadius, double minorRadius, const Color &color)
                : center(center), majorRadius(majorRadius), minorRadius(minorRadius), color(color) {};

        bool hit(const Ray &r, Interval ray_t, double &t_hit, vec3 &hit_normal, Color &hit_color, HitMat &rec) const override;
    };
}

#endif // B_OOP_400_LIL_4_1_RAYTRACER_THEO_LEMAIRE_TORUS_HPP
