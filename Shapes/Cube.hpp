//
// Created by Jean-Baptiste  Azan on 27/04/2024.
//


#include "Plane.hpp"
#include "../include/IShape.hpp"
#include <iostream>
#include <limits>
#include <cmath>
#include <memory>

namespace Raytracer {
    class Cube : public IShape {
    public:
        Plane planes[6];
        vec3 position;
        vec3 scale;
        vec3 rotation;
        std::shared_ptr<Material> mat;
        double size;
        Color color;

        Cube(vec3 position, vec3 scale, vec3 rotation, Color color, double size, std::shared_ptr<Material> mat)
                : position(position), scale(scale), rotation(rotation), size(size), color(color), mat(mat) {

            vec3 halfScale = scale * 0.5;
            planes[0] = Plane(position + vec3(0, 0, halfScale.z()), vec3(0, 0, 1), size, color, mat);
            planes[1] = Plane(position - vec3(0, 0, halfScale.z()), vec3(0, 0, -1), size, color, mat);
            planes[2] = Plane(position - vec3(halfScale.x(), 0, 0), vec3(-1, 0, 0), size, color, mat);
            planes[3] = Plane(position + vec3(halfScale.x(), 0, 0), vec3(1, 0, 0), size, color, mat);
            planes[4] = Plane(position + vec3(0, halfScale.y(), 0), vec3(0, 1, 0), size, color, mat);
            planes[5] = Plane(position - vec3(0, halfScale.y(), 0), vec3(0, -1, 0), size, color, mat);
        }

        bool hit(const Ray &r, Interval ray_t, double &t_hit, vec3 &hit_normal, Color &hit_color,
                 HitMat &rec) const override;
    };
}