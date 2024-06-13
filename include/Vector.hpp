/*
** EPITECH PROJECT, 2024
** B-OOP-400-LIL-4-1-raytracer-theo.lemaire
** File description:
** raytracer_engine.h
*/

#pragma once

#include <array>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <libconfig.h++>

namespace Raytracer {
    template<size_t N>
    class Vector {
    public:
        std::array<double, N> components;

        Vector() {
            components.fill(0);
        }

        Vector(std::initializer_list<double> list) {
            std::copy(list.begin(), list.end(), components.begin());
        }

        ~Vector() = default;

        double length() const {
            double sum = 0;
            for (auto component: components) {
                sum += component * component;
            }
            return std::sqrt(sum);
        }

        Vector<N> operator+(const Vector<N> &other) const {
            Vector<N> result;
            for (size_t i = 0; i < N; ++i) {
                result.components[i] = this->components[i] + other.components[i];
            }
            return result;
        }

        Vector<N> &operator+=(const Vector<N> &other) {
            for (size_t i = 0; i < N; ++i) {
                this->components[i] += other.components[i];
            }
            return *this;
        }

        Vector<N> operator-(const Vector<N> &other) const {
            Vector<N> result;
            for (size_t i = 0; i < N; ++i) {
                result.components[i] = this->components[i] - other.components[i];
            }
            return result;
        }

        Vector<N> &operator-=(const Vector<N> &other) {
            for (size_t i = 0; i < N; ++i) {
                this->components[i] -= other.components[i];
            }
            return *this;
        }

        Vector<N> operator*(double scalar) const {
            Vector<N> result;
            for (size_t i = 0; i < N; ++i) {
                result.components[i] = this->components[i] * scalar;
            }
            return result;
        }

        Vector<N> &operator*=(double scalar) {
            for (size_t i = 0; i < N; ++i) {
                this->components[i] *= scalar;
            }
            return *this;
        }

        Vector<N> operator/(double scalar) const {
            Vector<N> result;
            for (size_t i = 0; i < N; ++i) {
                result.components[i] = this->components[i] / scalar;
            }
            return result;
        }

        Vector<N> &operator/=(double scalar) {
            for (size_t i = 0; i < N; ++i) {
                this->components[i] /= scalar;
            }
            return *this;
        }

        double dot(const Vector<N> &other) const {
            double result = 0;
            for (size_t i = 0; i < N; ++i) {
                result += this->components[i] * other.components[i];
            }
            return result;
        }
    };
}