/*
** EPITECH PROJECT, 2024
** light
** File description:
** Point ight
*/

#ifndef POINTLIGHT_HPP_
#define POINTLIGHT_HPP_

#include "../include/ILight.hpp"
#include <memory>

namespace Raytracer {

    class PointLight : public ILight {
    private:
        vec3 position;
        Color intensity;

    public:
        PointLight(const vec3 &pos, const Color &color) :
                position(pos), intensity(color) {}

        vec3 getDirection(const point3 &hit_point) const override {
            return position - hit_point;
        }


        Color getIntensity(const point3 &hit_point) const override {
            (void) hit_point;
            return intensity;
        }
    };
}
#endif /* !POINTLIGHT_HPP_ */
