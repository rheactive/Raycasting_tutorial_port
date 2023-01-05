#ifndef PLAYER_HPP // include guard
#define PLAYER_HPP

#include <cmath>
#include <vector>

#include <SFML/Graphics.hpp>

#include "settings.hpp"
#include "input.hpp"
#include "map.hpp"

int get_tile (float x, float y) {
    return(floor(y) * MAP_WIDTH + floor(x) + 1);
};

bool walls_collide (float x, float y, std::map<int, int> walls) {
    bool collision = false;
    if(walls.count(get_tile(x + PLAYER_RADIUS, y + PLAYER_RADIUS)) == 1)
        collision = true;
    if(walls.count(get_tile(x + PLAYER_RADIUS, y - PLAYER_RADIUS)) == 1)
        collision = true;
    if(walls.count(get_tile(x - PLAYER_RADIUS, y + PLAYER_RADIUS)) == 1)
        collision = true;
    if(walls.count(get_tile(x - PLAYER_RADIUS, y - PLAYER_RADIUS)) == 1)
        collision = true;
    
    return(collision);
};

class Player {
    public:
        float x;
        float y;
        float angle;
        bool moved;

        Player () {
            x = PLAYER_X;
            y = PLAYER_Y;
            angle = PLAYER_ANGLE;
            moved = false;
        };

        void movement (InputState input_state, float frame_time, std::map<int, int> walls) {
            float cos_a = cos(angle);
            float sin_a = sin(angle);
            float vx = PLAYER_SPEED * cos_a * frame_time;
            float vy = PLAYER_SPEED * sin_a * frame_time;
            float va = PLAYER_ROT_SPEED * frame_time;
            float dx = 0.f;
            float dy = 0.f;

            if (input_state.keys["W"]) {
                dx += vx;
                dy += vy;
                moved = true;
            };

            if (input_state.keys["S"]) {
                dx += -vx;
                dy += -vy;
                moved = true;
            };

            if (input_state.keys["A"]) {
                dx += vy;
                dy += -vx;
                moved = true;
            };

            if (input_state.keys["D"]) {
                dx += -vy;
                dy += vx;
                moved = true;
            };

            if (!walls_collide(x + dx, y + dy, walls)) {
                x += dx;
                y += dy;
            } else {
                if (!walls_collide(x + dx, y, walls)) {
                    x += dx;
                } else {
                    if (!walls_collide(x, y + dy, walls)) {
                        y += dy;
                    };
            };
            };
            

            if (input_state.keys["Left"]) {
                angle -= va;
                moved = true;
            };

            if (input_state.keys["Right"]) {
                angle += va;
                moved = true;
            };

            angle = fmod(angle, 2 * PI);

        };

        void update (InputState input_state, float frame_time, std::map<int, int> walls) {
            moved = false;
            movement(input_state, frame_time, walls);
        };

        std::vector<sf::CircleShape> mini_copy () {
            std::vector<sf::CircleShape> to_draw;

            sf::CircleShape mini_me(PLAYER_RADIUS * TILE_WIDTH);
            mini_me.setPosition(sf::Vector2f(MINI_MAP_X + x * TILE_WIDTH, 
                MINI_MAP_Y + y * TILE_HEIGHT));
            mini_me.setFillColor(sf::Color::Yellow);
            mini_me.setOrigin(sf::Vector2f(PLAYER_RADIUS * TILE_WIDTH, 
                PLAYER_RADIUS * TILE_WIDTH));

            sf::CircleShape look_at(0.5 * PLAYER_RADIUS * TILE_WIDTH);
            look_at.setPosition(sf::Vector2f(MINI_MAP_X + (x + 2 * cos(angle)) * TILE_WIDTH, 
                MINI_MAP_Y + (y + 2 * sin(angle)) * TILE_HEIGHT));
            look_at.setFillColor(sf::Color::Red);
            look_at.setOrigin(sf::Vector2f(0.5 * PLAYER_RADIUS * TILE_WIDTH, 
                    0.5 * PLAYER_RADIUS * TILE_WIDTH));

            to_draw.push_back(mini_me);
            to_draw.push_back(look_at);

            return(to_draw);
        };
};



#endif /* PLAYER_HPP */