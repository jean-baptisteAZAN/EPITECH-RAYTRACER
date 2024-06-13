//
// Created by Jean-Baptiste  Azan on 23/04/2024.
//

#include "PointLight.hpp"

namespace Raytracer {

    extern "C"
    {
        std::unique_ptr<ILight> createLight(vec3 color, vec3 position) {
            return std::make_unique<PointLight>(position, color);
        }
    }
}