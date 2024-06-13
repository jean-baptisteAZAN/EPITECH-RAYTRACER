//
// Created by Jean-Baptiste  Azan on 23/04/2024.
//

#ifndef B_OOP_400_LIL_4_1_RAYTRACER_THEO_LEMAIRE_SPHERE_HPP
#define B_OOP_400_LIL_4_1_RAYTRACER_THEO_LEMAIRE_SPHERE_HPP

#include "../include/IShape.hpp"
#include "../include/Color.hpp"
#include "../include/Ray.hpp"
#include <memory>
#include <cmath>

namespace Raytracer {
    class Triangle : public IShape {
    private:
        point3 v0, v1, v2;  // Vertices of the triangle
        Color color;
        std::shared_ptr<Material> mat_ptr;

    public:
        Triangle(const point3 &v0, const point3 &v1, const point3 &v2, const Color &color, std::shared_ptr<Material> mat_ptr)
                : v0(v0), v1(v1), v2(v2), color(color), mat_ptr(mat_ptr) {};

        bool hit(const Ray &r, Interval ray_t, double &t_hit, vec3 &hit_normal, Color &hit_color, HitMat &rec) const override;
    };
}


#endif //B_OOP_400_LIL_4_1_RAYTRACER_THEO_LEMAIRE_SPHERE_HPP
