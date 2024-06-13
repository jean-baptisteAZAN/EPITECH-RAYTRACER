//
// Created by Jean-Baptiste  Azan on 23/04/2024.
//

#pragma once

#include "../include/IShape.hpp"
#include "../include/Color.hpp"
#include "../include/Ray.hpp"
#include <cmath>
#include <vector>
#include <memory>

namespace Raytracer {
    class Cones : public IShape {
    private:
        vec3 vertex;
        vec3 axis;
        double angle;
        double height;
        Color color;

    public:
        Cones(const vec3 &v, const vec3 &a, double ang, double h, const Color &color)
                : vertex(v), axis(a), angle(ang), height(h), color(color) {}

        bool hit(const Ray &r, Interval ray_t, double &t_hit, vec3 &hit_normal, Color &hit_color, HitMat &rec) const override;
    };
}
