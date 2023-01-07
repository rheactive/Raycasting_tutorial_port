#ifndef SPRITES_HPP // include guard
#define SPRITES_HPP

#include <cmath>
#include <vector>

#include <SFML/Graphics.hpp>

#include "settings.hpp"
#include "map.hpp"
#include "player.hpp"
#include "wall_render.hpp"

float distance(float x, float y)
{
    return (sqrt(x * x + y * y));
};

class Sprite
{
public:
    int map_id;
    int tex_id;
    float x;
    float y;
    float angle;
    float vx;
    float vy;
    bool moved;
    float dist_to_p;
    float dist_norm;
    float angle_to_p;
    float screen_x;
    float screen_height;
    float screen_width;
    int rays_start;
    int rays_end;
    int rays_number;
    float offset;
    bool on_screen;

    bool operator < (const Sprite& spr) const
    {
        return (dist_to_p > spr.dist_to_p);
    };

    Sprite(int map_id, const MapElement &map_sprite, Player &player)
    {
        map_id = map_id;
        tex_id = map_sprite.tex_id;
        x = map_sprite.x;
        y = map_sprite.y;
        angle = 0.f;
        vx = 0.f;
        vy = 0.f;
        moved = false;
        float dx = x - player.x;
        float dy = y - player.y;
        dist_to_p = distance(dx, dy);
        angle_to_p = atan2(dy, dx);
        float delta = angle_to_p - player.angle;
        if ((dx > 0.f && player.angle > PI) || (dx < 0.f && dy < 0.f))
        {
            delta += 2.0f * PI;
        };
        dist_norm = dist_to_p * cos(delta);
        float delta_rays = delta / ANGLE_STEP;
        int rays_shift = RAYS_NUMBER / 2 + delta_rays;
        screen_x = rays_shift * STEP_SIZE;
        screen_height = SCREEN_DISTANCE / dist_norm;
        screen_width = screen_height;
        rays_number = screen_width / STEP_SIZE;
        rays_start = rays_shift - screen_width / STEP_SIZE / 2;
        rays_end = rays_start + rays_number;
        offset = 0.f;
        if (rays_start < 0)
        {
            offset = 0.5 - screen_x / screen_width;
            rays_start = 0;
        };
        if (rays_end > RAYS_NUMBER)
        {
            rays_end = RAYS_NUMBER;
        };

        rays_number = rays_end - rays_start;

        if (rays_start < RAYS_NUMBER && rays_end > 0 && rays_number > 0 && dist_norm > 0.5)
        {
            on_screen = true;
        }
        else
        {
            on_screen = false;
        };
    };

    sf::VertexArray draw_sprite(const std::vector<Ray> &rays)
    {
        sf::VertexArray sprite_quads(sf::Quads, rays_number * 4);

        sprite_quads[0].position = sf::Vector2f(screen_x - 0.5f * screen_width,
                                                HALF_HEIGHT + 0.5 * screen_height);
        sprite_quads[1].position = sf::Vector2f(screen_x - 0.5f * screen_width,
                                                HALF_HEIGHT - 0.5 * screen_height);
        sprite_quads[2].position = sf::Vector2f(screen_x + 0.5f * screen_width,
                                                HALF_HEIGHT - 0.5 * screen_height);
        sprite_quads[3].position = sf::Vector2f(screen_x + 0.5f * screen_width,
                                                HALF_HEIGHT + 0.5 * screen_height);

        int id = tex_id;

        for (int k = rays_start; k < rays_end; k++) {
            if (dist_norm > rays[k].distance)
                id = 0;
        };

        sprite_quads[0].texCoords = sf::Vector2f(0.f, (id + 1) * SPRITE_TEXTURE_SIZE);
        sprite_quads[1].texCoords = sf::Vector2f(0.f, id * SPRITE_TEXTURE_SIZE);
        sprite_quads[2].texCoords = sf::Vector2f(0.f + SPRITE_TEXTURE_SIZE, id * SPRITE_TEXTURE_SIZE);
        sprite_quads[3].texCoords = sf::Vector2f(0.f + SPRITE_TEXTURE_SIZE, (id + 1) * SPRITE_TEXTURE_SIZE);

        return (sprite_quads);
    };
};

class Sprites
{
public:
    std::vector<Sprite> sprites;

    Sprites(int map_id, Map &map, Player &player)
    {
        for (auto const &s : map.sprites)
        {
            Sprite sprite(map_id, s.second, player);
            if (sprite.on_screen)
            {
                sprites.push_back(sprite);
            };
        };

        std::sort(sprites.begin(), sprites.end());
    };

    std::vector<sf::VertexArray> draw_sprites(const std::vector<Ray> &rays)
    {
        std::vector<sf::VertexArray> sprite_quads;

        for (int j = 0; j < sprites.size(); j++)
        {
            sprite_quads.push_back(sprites[j].draw_sprite(rays));
        };

        return (sprite_quads);
    };
};

#endif /* SPRITES_HPP */