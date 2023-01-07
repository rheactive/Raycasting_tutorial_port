#ifndef FLOOR_RENDER_HPP // include guard
#define FLOOR_RENDER_HPP

#include <cmath>
#include <vector>

#include <SFML/Graphics.hpp>

#include "settings.hpp"
#include "player.hpp"

class RayFloor
{
public:
    sf::Vector2f uv11;
    sf::Vector2f uv12;
    sf::Vector2f uv21;
    sf::Vector2f uv22;

    RayFloor()
    {
        uv11 = sf::Vector2f(0.f, 0.f);
        uv12 = sf::Vector2f(0.f, 0.f);
        uv21 = sf::Vector2f(0.f, 0.f);
        uv22 = sf::Vector2f(0.f, 0.f);
    };
};

class Raycast_floor
{
public:
    std::vector<RayFloor> rays;

    Raycast_floor(Player &player)
    {
        float screen_dist = 1.f;
        float half_width = screen_dist * tan(HALF_FOV);
        float half_height = half_width * WINDOW_HEIGHT / WINDOW_WIDTH;
        float scale = half_height / HALF_HEIGHT;

        sf::Vector2f player_pos = sf::Vector2f(player.x, player.y);
        float a = player.angle;
        float cos_a = cos(a);
        float sin_a = sin(a);

        float min_ray_depth = screen_dist / half_height * PLAYER_Z;
        float ray_depth = min_ray_depth;
        float ray_screen_height = 0.f;

        while (ray_depth < MAX_DISTANCE) {
            RayFloor ray;

            ray_screen_height = ray_screen_height + scale;

            float texture_height = screen_dist 
                / (half_height - ray_screen_height) * PLAYER_Z - ray_depth;

            float texture_half_width = half_width / screen_dist 
                * (ray_depth + texture_height / 2.0);

            sf::Vector2f ray_dir1 = sf::Vector2f(
                ray_depth * cos_a, 
                ray_depth * sin_a
            );

            sf::Vector2f ray_dir2 = sf::Vector2f(
                (ray_depth + texture_height) * cos_a, 
                (ray_depth + texture_height) * sin_a
            );

            sf::Vector2f perp_dir = sf::Vector2f(
                texture_half_width * sin_a, 
                -texture_half_width * cos_a
            );

            ray.uv11 = (player_pos + ray_dir2 + perp_dir) / FLOOR_SIZE;
            ray.uv12 = (player_pos + ray_dir2 - perp_dir) / FLOOR_SIZE;
            ray.uv21 = (player_pos + ray_dir1 + perp_dir) / FLOOR_SIZE;
            ray.uv22 = (player_pos + ray_dir1 - perp_dir) / FLOOR_SIZE;

            ray.uv11 *= FLOOR_TEXTURE_SIZE;
            ray.uv12 *= FLOOR_TEXTURE_SIZE;
            ray.uv21 *= FLOOR_TEXTURE_SIZE;
            ray.uv22 *= FLOOR_TEXTURE_SIZE;

            rays.push_back(ray);

            ray_depth = ray_depth + texture_height;
        };

    };

    sf::VertexArray draw_floor () {

        int rays_number = rays.size();

        sf::VertexArray to_draw(sf::Quads, rays_number * 4);

        float height_offset;

        for (int k = 0; k < rays_number; k++)
        {
            height_offset = STEP_SIZE * k / 2.f;
            
            to_draw[4 * k].position = sf::Vector2f(0.0, WINDOW_HEIGHT - (height_offset + STEP_SIZE));
            to_draw[4 * k + 1].position = sf::Vector2f(0.0, WINDOW_HEIGHT - height_offset);
            to_draw[4 * k + 2].position = sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT - height_offset);
            to_draw[4 * k + 3].position = sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT - (height_offset + STEP_SIZE));

            to_draw[4 * k].texCoords = rays[k].uv11;
            to_draw[4 * k + 1].texCoords = rays[k].uv21;
            to_draw[4 * k + 2].texCoords = rays[k].uv22;
            to_draw[4 * k + 3].texCoords = rays[k].uv12;
        };

        return(to_draw);
    };

    sf::VertexArray draw_ceiling () {

        int rays_number = rays.size();

        sf::VertexArray to_draw(sf::Quads, rays_number * 4);

        float height_offset;

        for (int k = 0; k < rays_number; k++)
        {
            height_offset = STEP_SIZE * k / 2.f;
            
            to_draw[4 * k].position = sf::Vector2f(0.0, height_offset);
            to_draw[4 * k + 1].position = sf::Vector2f(0.0, height_offset + STEP_SIZE);
            to_draw[4 * k + 2].position = sf::Vector2f(WINDOW_WIDTH, height_offset + STEP_SIZE);
            to_draw[4 * k + 3].position = sf::Vector2f(WINDOW_WIDTH, height_offset);

            to_draw[4 * k].texCoords = rays[k].uv11;
            to_draw[4 * k + 1].texCoords = rays[k].uv21;
            to_draw[4 * k + 2].texCoords = rays[k].uv22;
            to_draw[4 * k + 3].texCoords = rays[k].uv12;
        };

        return(to_draw);
    };
};

#endif /* FLOOR_RENDER_HPP */