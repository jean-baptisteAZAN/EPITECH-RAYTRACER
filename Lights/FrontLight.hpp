//
// Created by Jean-Baptiste  Azan on 23/04/2024.
//

#ifndef B_OOP_400_LIL_4_1_RAYTRACER_THEO_LEMAIRE_FRONTLIGHT_HPP
#define B_OOP_400_LIL_4_1_RAYTRACER_THEO_LEMAIRE_FRONTLIGHT_HPP

#include "../include/ILight.hpp"
#include <memory>

namespace Raytracer {

    class FrontLight : public ILight {
    private:
        vec3 direction;
        Color intensity;

    public:

        FrontLight(const vec3 &direction, const Color &intensity)
                : direction(unit_vector(direction)), intensity(intensity) {}

        vec3 getDirection(const point3 &hit_point) const override {
            (void) hit_point;
            return direction;
        }

        Color getIntensity(const point3 &hit_point) const override {
            (void) hit_point;
            return intensity;
        }
    };
}
#endif //B_OOP_400_LIL_4_1_RAYTRACER_THEO_LEMAIRE_FRONTLIGHT_HPP
