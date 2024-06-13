//
// Created by Jean-Baptiste  Azan on 23/04/2024.
//

#ifndef B_OOP_400_LIL_4_1_RAYTRACER_THEO_LEMAIRE_SPHERE_HPP
#define B_OOP_400_LIL_4_1_RAYTRACER_THEO_LEMAIRE_SPHERE_HPP

#include "../include/IShape.hpp"
#include "../include/Color.hpp"
#include "../include/Ray.hpp"
#include <memory>

namespace Raytracer {
    class Sphere : public IShape {
    private:
        point3 center;
        double radius;
        Color color;
        std::shared_ptr<Material> mat;

    public:
        Sphere(const point3 &center, double radius, const Color &color, std::shared_ptr<Material> m)
                : center(center), radius(fmax(0, radius)), color(color), mat(m) {};

        bool hit(const Ray &r, Interval ray_t, double &t_hit, vec3 &hit_normal, Color &hit_color,
                 HitMat &rec) const override;
    };
}
#endif //B_OOP_400_LIL_4_1_RAYTRACER_THEO_LEMAIRE_SPHERE_HPP
