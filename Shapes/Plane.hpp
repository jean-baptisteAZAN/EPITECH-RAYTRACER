//
// Created by Jean-Baptiste  Azan on 24/04/2024.
//

#ifndef B_OOP_400_LIL_4_1_RAYTRACER_THEO_LEMAIRE_PLANE_HPP
#define B_OOP_400_LIL_4_1_RAYTRACER_THEO_LEMAIRE_PLANE_HPP

#include "../include/IShape.hpp"
#include "../include/Color.hpp"
#include "../include/Ray.hpp"
#include <memory>

namespace Raytracer {

    class Plane : public IShape {
    private:
        point3 position;
        vec3 normal;
        double size;
        Color color;
        std::shared_ptr<Material> mat; // Material

    public:
        Plane() = default;

        virtual ~Plane() = default;

        Plane(const point3 &position, const vec3 &normal, double size, const Color &color,
              std::shared_ptr<Material> mat)
                : position(position), normal(normal), size(size), color(color), mat(mat) {};

        bool hit(const Ray &r, Interval ray_t, double &t_hit, vec3 &hit_normal, Color &hit_color,
                 HitMat &rec) const override;
    };
}
#endif //B_OOP_400_LIL_4_1_RAYTRACER_THEO_LEMAIRE_PLANE_HPP