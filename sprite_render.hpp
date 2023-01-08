#ifndef SPRITE_RENDER_HPP // include guard
#define SPRITES_RENDER_HPP

#include <cmath>
#include <vector>

#include <SFML/Graphics.hpp>

#include "settings.hpp"
#include "wall_render.hpp"
#include "sprites.hpp"

class Draw_sprite
{
public:
    sf::VertexArray sprite_quads;

    Draw_sprite (const std::vector<Ray> &rays, const Sprite &sprite)
    {
        sf::VertexArray sprite_quads(sf::Quads, sprite.rays_number * 4);

        float scale;
        float width;
        float x1;

        for (int k = 0; k < sprite.rays_number; k++)
        {
            scale = sprite.screen_height / SPRITE_TEXTURE_SIZE;
            width = STEP_SIZE / scale;
            x1 = k / sprite.rays_number * SPRITE_TEXTURE_SIZE;

            if (sprite.dist_norm < rays[k + sprite.rays_shift].distance) {
                sprite_quads[4 * k].position = sf::Vector2f(sprite.screen_x + k * STEP_SIZE, 
                    HALF_HEIGHT + 0.5 * sprite.screen_height);
                sprite_quads[4 * k + 1].position = sf::Vector2f(sprite.screen_x + k * STEP_SIZE, 
                    HALF_HEIGHT - 0.5 * sprite.screen_height);
                sprite_quads[4 * k + 2].position = sf::Vector2f(sprite.screen_x + k * STEP_SIZE + STEP_SIZE, 
                    HALF_HEIGHT - 0.5 * sprite.screen_height);
                sprite_quads[4 * k + 3].position = sf::Vector2f(sprite.screen_x + k * STEP_SIZE + STEP_SIZE, 
                    HALF_HEIGHT + 0.5 * sprite.screen_height);

                sprite_quads[4 * k].texCoords = sf::Vector2f(x1, sprite.tex_id * SPRITE_TEXTURE_SIZE);
                sprite_quads[4 * k + 1].texCoords = sf::Vector2f(x1, (sprite.tex_id + 1) * SPRITE_TEXTURE_SIZE);
                sprite_quads[4 * k + 2].texCoords = sf::Vector2f(x1 + width, (sprite.tex_id + 1) * SPRITE_TEXTURE_SIZE);
                sprite_quads[4 * k + 3].texCoords = sf::Vector2f(x1 + width, sprite.tex_id * SPRITE_TEXTURE_SIZE);
            } else {
                sprite_quads[4 * k].position = sf::Vector2f(sprite.screen_x + k * STEP_SIZE, 
                    HALF_HEIGHT + 0.5 * sprite.screen_height);
                sprite_quads[4 * k + 1].position = sf::Vector2f(sprite.screen_x + k * STEP_SIZE, 
                    HALF_HEIGHT - 0.5 * sprite.screen_height);
                sprite_quads[4 * k + 2].position = sf::Vector2f(sprite.screen_x + k * STEP_SIZE + STEP_SIZE, 
                    HALF_HEIGHT - 0.5 * sprite.screen_height);
                sprite_quads[4 * k + 3].position = sf::Vector2f(sprite.screen_x + k * STEP_SIZE + STEP_SIZE, 
                    HALF_HEIGHT + 0.5 * sprite.screen_height);

                sprite_quads[4 * k].texCoords = sf::Vector2f(x1, 0.f);
                sprite_quads[4 * k + 1].texCoords = sf::Vector2f(x1, SPRITE_TEXTURE_SIZE);
                sprite_quads[4 * k + 2].texCoords = sf::Vector2f(x1 + width, SPRITE_TEXTURE_SIZE);
                sprite_quads[4 * k + 3].texCoords = sf::Vector2f(x1 + width, 0.f);
            };
            
            
        };
    };
};


#endif /* SPRITES_RENDER_HPP */