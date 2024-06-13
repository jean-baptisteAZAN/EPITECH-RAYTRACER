//
// Created by Jean-Baptiste  Azan on 27/04/2024.
//

#ifndef B_OOP_400_LIL_4_1_RAYTRACER_THEO_LEMAIRE_CYLINDER_HPP
#define B_OOP_400_LIL_4_1_RAYTRACER_THEO_LEMAIRE_CYLINDER_HPP
#include "../include/IShape.hpp"
#include "../include/Color.hpp"
#include "../include/Ray.hpp"
#include <memory>

namespace Raytracer {
    class Cylinder : public IShape {
    private:
        point3 center;
        vec3 axis;
        double radius;
        double height;
        Color color;
        vec3 rotation;
        float PI = 3.14159265359;
        std::shared_ptr<Material> mat;

    public:
        Cylinder(const point3 &center, const vec3 &axis, double radius, double height, const Color &color, std::shared_ptr<Material> m, const vec3 rotation)
                : center(center), axis(axis), radius(radius), height(height), color(color), mat(m), rotation(rotation) {};

        bool hit(const Ray &r, Interval ray_t, double &t_hit, vec3 &hit_normal, Color &hit_color, HitMat &rec) const override;
        vec3 rotateY(const vec3& p, double angle) const;
        vec3 rotateX(const vec3& p, double angle) const;
        vec3 rotateZ(const vec3& p, double angle) const;
    };
}



#endif //B_OOP_400_LIL_4_1_RAYTRACER_THEO_LEMAIRE_CYLINDER_HPP
