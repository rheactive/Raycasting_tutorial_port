#ifndef SPRITES_HPP // include guard
#define SPRITES_HPP

#include <cmath>
#include <vector>
#include <map>

#include <SFML/Graphics.hpp>

#include "settings.hpp"
#include "map.hpp"
#include "player.hpp"
#include "wall_render.hpp"

float distance(float x, float y)
{
    return (sqrt(x * x + y * y));
};

class SpriteTexData {
    public:
        std::map<int, float> sprite_width;
        std::map<int, int> animations;
        std::map<int, int> anim_delay;
        SpriteTexData () {
            sprite_width[1] = 85.f;
            sprite_width[2] = 64.f;
            sprite_width[3] = 32.f;

            animations[1] = 1;
            animations[2] = 8;
            animations[3] = 3;

            anim_delay[1] = 100;
            anim_delay[2] = 9;
            anim_delay[3] = 20;
        };
};


class Sprite
{
public:
    int map_id;
    int tex_id;
    float tex_width;
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
    bool on_screen;
    int animations;
    int anim_delay;
    int anim_count;

    bool operator < (const Sprite& spr) const
    {
        return (dist_to_p > spr.dist_to_p);
    };

    void animate (const int &frame_count) {
        if (animations > 1) {
            anim_count = frame_count / anim_delay;
        };
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
        SpriteTexData sprite_tex_data;
        animations = sprite_tex_data.animations[tex_id];
        anim_delay = sprite_tex_data.anim_delay[tex_id];
        anim_count = 0;
        tex_width = sprite_tex_data.sprite_width[tex_id];
        screen_width = screen_height * tex_width / SPRITE_TEXTURE_SIZE;
        int rays_number = screen_width / STEP_SIZE;
        rays_start = rays_shift - screen_width / STEP_SIZE / 2;
        rays_end = rays_start + rays_number;
        if (rays_start < 0)
        {
            rays_start = 0;
        };
        if (rays_end > RAYS_NUMBER)
        {
            rays_end = RAYS_NUMBER;
        };

        float visible_part = (rays_end - rays_start) * 1.f / rays_number * 1.f;

        rays_number = rays_end - rays_start;

        if (visible_part > 0.1f && dist_norm > 0.5)
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
        sf::VertexArray sprite_quads(sf::Quads, 4);

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

        sprite_quads[0].texCoords = sf::Vector2f(anim_count * 1.f * tex_width, (id + 1) * SPRITE_TEXTURE_SIZE);
        sprite_quads[1].texCoords = sf::Vector2f(anim_count * 1.f * tex_width, id * SPRITE_TEXTURE_SIZE);
        sprite_quads[2].texCoords = sf::Vector2f((anim_count + 1.f) * tex_width, id * SPRITE_TEXTURE_SIZE);
        sprite_quads[3].texCoords = sf::Vector2f((anim_count + 1.f) * tex_width, (id + 1) * SPRITE_TEXTURE_SIZE);

        return (sprite_quads);
    };
};

class Sprites
{
public:
    std::vector<Sprite> sprites;

    Sprites(int map_id, const int &frame_count, Map &map, Player &player)
    {
        for (auto const &s : map.sprites)
        {
            Sprite sprite(map_id, s.second, player);
            if (sprite.on_screen)
            {
                sprite.animate(frame_count);
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