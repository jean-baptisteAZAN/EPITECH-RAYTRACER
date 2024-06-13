/*
** EPITECH PROJECT, 2024
** iform
** File description:
** IForm
*/

#ifndef IFORM_HPP_
#define IFORM_HPP_

#include <fstream>
#include <iostream>
#include <vector>

namespace Raytracer {

    class IForm {
    public:
        IForm() = default;

        virtual ~IForm() = default;

        struct Vec3 {
            float x;
            float y;
            float z;
        };
        struct Object {
            std::string type;
            Vec3 position;
        };

        virtual std::vector<std::pair<Vec3, std::string>> init(std::vector<Object> object) = 0;

    private:
        std::vector<std::pair<Vec3, std::string>> _objects;
    };
}
#endif /* !IFORM_HPP_ */
