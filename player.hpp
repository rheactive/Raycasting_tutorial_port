#ifndef PLAYER_HPP // include guard
#define PLAYER_HPP

#include <cmath>
#include <vector>

#include <SFML/Graphics.hpp>

#include "settings.hpp"
#include "input.hpp"
#include "map.hpp"

float round_angle(float &angle) {
    float a = angle / PI;
    if (a >= 2.0f) {
        angle = angle - 2.0f * PI;
        round_angle(angle);
    }
    if (a < 0.0) {
        angle = angle + 2.0f * PI;
        round_angle(angle);
    }
    return(angle);
};

int get_tile(const float &x, const float &y)
{
    return (floor(y) * MAP_WIDTH + floor(x) + 1);
};

int walls_collide(const float &x, const float &y, Map &map)
{
    int wall_id = 0;
    int tile = get_tile(x + PLAYER_RADIUS, y + PLAYER_RADIUS);
    if (map.walls.count(tile) == 1)
        wall_id = map.walls[tile].tex_id;
    tile = get_tile(x + PLAYER_RADIUS, y - PLAYER_RADIUS);
    if (map.walls.count(tile) == 1)
        wall_id = map.walls[tile].tex_id;
    tile = get_tile(x - PLAYER_RADIUS, y + PLAYER_RADIUS);
    if (map.walls.count(tile) == 1)
        wall_id = map.walls[tile].tex_id;
    tile = get_tile(x - PLAYER_RADIUS, y - PLAYER_RADIUS);
    if (map.walls.count(tile) == 1)
        wall_id = map.walls[tile].tex_id;

    return (wall_id);
};

int sprites_collide(const float &x, const float &y, Map &map)
{
    int sprite_id = 0;
    int tile = get_tile(x + PLAYER_RADIUS, y + PLAYER_RADIUS);
    if (map.sprites.count(tile) == 1)
        sprite_id = map.sprites[tile].tex_id;
    tile = get_tile(x + PLAYER_RADIUS, y - PLAYER_RADIUS);
    if (map.sprites.count(tile) == 1)
        sprite_id = map.sprites[tile].tex_id;
    tile = get_tile(x - PLAYER_RADIUS, y + PLAYER_RADIUS);
    if (map.sprites.count(tile) == 1)
        sprite_id = map.sprites[tile].tex_id;
    tile = get_tile(x - PLAYER_RADIUS, y - PLAYER_RADIUS);
    if (map.sprites.count(tile) == 1)
        sprite_id = map.sprites[tile].tex_id;

    return (sprite_id);
};

class Player
{
public:
    float x;
    float y;
    float angle;
    bool moved;
    int map_id;

    Player()
    {
        x = PLAYER_X;
        y = PLAYER_Y;
        angle = PLAYER_ANGLE;
        moved = false;
        map_id = 1;
    };

    void movement(InputState &input_state, const float &frame_time, Map &map)
    {
        float cos_a = cos(angle);
        float sin_a = sin(angle);
        float vx = PLAYER_SPEED * cos_a * frame_time;
        float vy = PLAYER_SPEED * sin_a * frame_time;
        float va = PLAYER_ROT_SPEED * frame_time;
        float dx = 0.f;
        float dy = 0.f;

        if (input_state.keys["W"])
        {
            dx += vx;
            dy += vy;
            moved = true;
        };

        if (input_state.keys["S"])
        {
            dx += -vx;
            dy += -vy;
            moved = true;
        };

        if (input_state.keys["A"])
        {
            dx += vy;
            dy += -vx;
            moved = true;
        };

        if (input_state.keys["D"])
        {
            dx += -vy;
            dy += vx;
            moved = true;
        };

        int wc1 = walls_collide(x + dx, y + dy, map);
        int wc2 = walls_collide(x + dx, y, map);
        int wc3 = walls_collide(x, y + dy, map);
        int sc1 = sprites_collide(x + dx, y + dy, map);
        int sc2 = sprites_collide(x + dx, y, map);
        int sc3 = sprites_collide(x, y + dy, map);

        if (wc1 == 5)
        {
            if (map_id == 1) {
                map_id = 2;
            }
            else if (map_id == 2) {
                map_id = 1;
            };
            x = 1.5;
            y = 4.5;
        }
        else if (wc1 == 0 && sc1 == 0)
        {
            x += dx;
            y += dy;
        }
        else if (wc2 == 0 && sc2 == 0)
        {
            x += dx;
        }
        else if (wc3 == 0 && sc3 == 0)
        {
            y += dy;
        };

        if (input_state.keys["Left"])
        {
            angle -= va;
            moved = true;
        };

        if (input_state.keys["Right"])
        {
            angle += va;
            moved = true;
        };

        angle = round_angle(angle);
    };

    void update(InputState &input_state, const float &frame_time, Map &map)
    {
        moved = false;
        movement(input_state, frame_time, map);
    };

    std::vector<sf::CircleShape> mini_copy()
    {
        std::vector<sf::CircleShape> to_draw;

        sf::CircleShape mini_me(PLAYER_RADIUS * TILE_WIDTH);
        mini_me.setPosition(sf::Vector2f(MINI_MAP_X + x * TILE_WIDTH,
            MINI_MAP_Y + y * TILE_HEIGHT));
        mini_me.setFillColor(sf::Color::Blue);
        mini_me.setOrigin(sf::Vector2f(PLAYER_RADIUS * TILE_WIDTH,
            PLAYER_RADIUS * TILE_WIDTH));

        sf::CircleShape look_at(0.5 * PLAYER_RADIUS * TILE_WIDTH);
        look_at.setPosition(sf::Vector2f(MINI_MAP_X + (x + 5 * cos(angle)) * TILE_WIDTH,
            MINI_MAP_Y + (y + 5 * sin(angle)) * TILE_HEIGHT));
        look_at.setFillColor(sf::Color::Red);
        look_at.setOrigin(sf::Vector2f(0.5 * PLAYER_RADIUS * TILE_WIDTH,
            0.5 * PLAYER_RADIUS * TILE_WIDTH));

        to_draw.push_back(mini_me);
        to_draw.push_back(look_at);

        return (to_draw);
    };
};

#endif /* PLAYER_HPP */