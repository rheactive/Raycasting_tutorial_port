#ifndef WALL_RENDER_HPP // include guard
#define WALL_RENDER_HPP

#include <cmath>
#include <vector>

#include <SFML/Graphics.hpp>

#include "settings.hpp"
#include "map.hpp"
#include "player.hpp"

class Ray
{
public:
    float angle;
    float distance;
    float x_end;
    float y_end;
    float height;
    float offset;
    int wall_id;

    Ray(const float &angle1)
    {
        angle = angle1;
        distance = 0.f;
        x_end = 0.f;
        y_end = 0.f;
        height = 0.f;
        offset = 0.f;
        wall_id = 0;
    };
};

class Raycast_walls
{
public:
    std::vector<Ray> rays;
    float x;
    float y;
    float camera_shake;

    Raycast_walls(Player &player, Map &map)
    {
        x = player.x;
        y = player.y;

        float tile_x = floor(x);
        float tile_y = floor(y);

        float angle = player.angle;
        float ray_angle = angle - HALF_FOV + TOLERANCE;

        camera_shake = head_bob(player.x, player.y);

        for (int k = 0; k < RAYS_NUMBER; k++)
        {

            float delta_a = angle - ray_angle;

            float cos_a = cos(ray_angle);
            float sin_a = sin(ray_angle);

            Ray ray(ray_angle);

            int wall_hor = 0;
            int wall_vert = 0;

            // Horizontal mini-map lines
            float y_hor;
            float dy_hor;

            if (sin_a > 0.f)
            {
                y_hor = tile_y + 1.f;
                dy_hor = 1.f;
            }
            else
            {
                y_hor = tile_y - TOLERANCE;
                dy_hor = -1.f;
            };

            float dist_hor = (y_hor - y) / sin_a;
            float x_hor = x + dist_hor * cos_a;
            float d_dist_hor = dy_hor / sin_a;
            float dx_hor = d_dist_hor * cos_a;

            bool check_hor = false;

            while (dist_hor < MAX_DISTANCE && !check_hor)
            {
                int tile = get_tile(x_hor, y_hor);
                if (map.walls.count(tile) == 1)
                {
                    wall_hor = map.walls[tile].tex_id;
                    check_hor = true;
                }
                else
                {
                    x_hor += dx_hor;
                    y_hor += dy_hor;
                    dist_hor += d_dist_hor;
                };
            };

            // Vertical mini-map lines
            float x_vert;
            float dx_vert;

            if (cos_a > 0.f)
            {
                x_vert = tile_x + 1.f;
                dx_vert = 1.f;
            }
            else
            {
                x_vert = tile_x - TOLERANCE;
                dx_vert = -1.f;
            };

            float dist_vert = (x_vert - x) / cos_a;
            float y_vert = y + dist_vert * sin_a;
            float d_dist_vert = dx_vert / cos_a;
            float dy_vert = d_dist_vert * sin_a;

            bool check_vert = false;

            while (dist_vert < MAX_DISTANCE && !check_vert)
            {
                int tile = get_tile(x_vert, y_vert);
                if (map.walls.count(tile) == 1)
                {
                    wall_vert = map.walls[tile].tex_id;
                    check_vert = true;
                }
                else
                {
                    x_vert += dx_vert;
                    y_vert += dy_vert;
                    dist_vert += d_dist_vert;
                };
            };

            // compare distances
            if (dist_vert > dist_hor)
            {
                ray.distance = dist_hor * cos(delta_a);
                ray.wall_id = wall_hor;
                ray.x_end = x_hor;
                ray.y_end = y_hor;
                ray.height = SCREEN_DISTANCE / ray.distance;
                if (sin_a > 0.0)
                {
                    ray.offset = 1.0 - x_hor + floor(x_hor);
                }
                else
                {
                    ray.offset = x_hor - floor(x_hor);
                };
            }
            else
            {
                ray.distance = dist_vert * cos(delta_a);
                ray.wall_id = wall_vert;
                ray.x_end = x_vert;
                ray.y_end = y_vert;
                ray.height = SCREEN_DISTANCE / ray.distance;
                if (cos_a > 0.0)
                {
                    ray.offset = y_vert - floor(y_vert);
                }
                else
                {
                    ray.offset = 1.0 - y_vert + floor(y_vert);
                };
            };

            rays.push_back(ray);

            float da = STEP_REL * pow(cos(delta_a), 2.0);

            if (k * 2 < RAYS_NUMBER) {
                ray_angle += da;
            } else {
                ray_angle += da / (1.0 + STEP_REL * fabs(sin((2.0 * delta_a))));
            };
        };
    };

    sf::VertexArray map_rays () {

        sf::VertexArray to_draw(sf::TriangleFan, MINI_MAP_RAYS_NUMBER + 1);
        
        to_draw[0].position = sf::Vector2f(MINI_MAP_X + x * TILE_WIDTH,
            MINI_MAP_Y + y * TILE_HEIGHT);
        
        to_draw[0].color = sf::Color::Yellow;

        for (int k = 0; k < MINI_MAP_RAYS_NUMBER; k++)
        {
            to_draw[k + 1].position = sf::Vector2f(MINI_MAP_X + rays[4 * k].x_end * TILE_WIDTH,
            MINI_MAP_Y + rays[4 * k].y_end * TILE_HEIGHT);
        
            to_draw[k + 1].color = sf::Color::Yellow;
        };

        return(to_draw);
    };

    sf::VertexArray draw_walls () {

        sf::VertexArray to_draw(sf::Quads, RAYS_NUMBER * 4);

        float scale;
        float width;
        float x1;

        for (int k = 0; k < RAYS_NUMBER; k++)
        {
            scale = rays[k].height / TILE_TEXTURE_SIZE;
            width = STEP_SIZE / scale;
            x1 = rays[k].offset * TILE_TEXTURE_SIZE;

            float y1 = 0.5 * (1.f + 2.f * camera_shake);
            float y2 = 0.5 * (1.f - 2.f * camera_shake);
            
            to_draw[4 * k].position = sf::Vector2f(k * STEP_SIZE, HALF_HEIGHT + y1 * rays[k].height);
            to_draw[4 * k + 1].position = sf::Vector2f(k * STEP_SIZE, HALF_HEIGHT - y2 * rays[k].height);
            to_draw[4 * k + 2].position = sf::Vector2f(k * STEP_SIZE + STEP_SIZE, HALF_HEIGHT - y2 * rays[k].height);
            to_draw[4 * k + 3].position = sf::Vector2f(k * STEP_SIZE + STEP_SIZE, HALF_HEIGHT + y1 * rays[k].height);

            to_draw[4 * k].texCoords = sf::Vector2f(x1, (rays[k].wall_id-1) * TILE_TEXTURE_SIZE);
            to_draw[4 * k + 1].texCoords = sf::Vector2f(x1, rays[k].wall_id * TILE_TEXTURE_SIZE);
            to_draw[4 * k + 2].texCoords = sf::Vector2f(x1 + width, rays[k].wall_id * TILE_TEXTURE_SIZE);
            to_draw[4 * k + 3].texCoords = sf::Vector2f(x1 + width, (rays[k].wall_id-1) * TILE_TEXTURE_SIZE);
        };

        return(to_draw);
    };
};

#endif /* WALL_RENDER_HPP */