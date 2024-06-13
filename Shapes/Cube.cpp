//
// Created by Jean-Baptiste  Azan on 23/04/2024.
//

#include "Cube.hpp"

namespace Raytracer {
    extern "C"
    {
    std::unique_ptr<IShape>
        createCube(vec3 position, vec3 scale, vec3 rotation, Color color, double size, std::shared_ptr<Material> mat) {
            return std::make_unique<Cube>(position, scale, rotation, color, size, mat);
        }
    }

    bool Cube::hit(const Ray &r, Interval ray_t, double &t_hit, vec3 &hit_normal, Color &hit_color, HitMat &rec) const {
        double nearest_t = std::numeric_limits<double>::infinity();
        bool hit_anything = false;
        HitMat temp_rec;

        for (const auto &plane: planes) {
            double local_t_hit;
            vec3 local_hit_normal;
            Color local_hit_color;

            if (plane.hit(r, ray_t, local_t_hit, local_hit_normal, local_hit_color, temp_rec) &&
                local_t_hit < nearest_t) {
                nearest_t = local_t_hit;
                hit_normal = local_hit_normal;
                hit_color = local_hit_color;
                rec = temp_rec;
                rec.p = r.at(nearest_t);
                rec.set_face_normal(r, hit_normal);
                rec.mat_ptr = mat;
                hit_anything = true;
            }
        }

        t_hit = nearest_t;
        return hit_anything;
    }

}
