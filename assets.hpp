#ifndef ASSETS_HPP // include guard
#define ASSETS_HPP

#include <vector>

#include <SFML/Graphics.hpp>

class Assets {
    public:
        std::vector<sf::Texture> wall_textures;
        std::vector<sf::Texture> sky_textures;
        std::vector<sf::Texture> ceil_textures;
        std::vector<sf::Texture> floor_textures;
        std::vector<sf::Texture> sprite_textures;

        Assets () {
            sf::Texture texture;
            texture.loadFromFile("resources/textures/walls.png");
            wall_textures.push_back(texture);
            texture.loadFromFile("resources/textures/sky.png");
            sky_textures.push_back(texture);
            texture.loadFromFile("resources/textures/floor1.png");
            floor_textures.push_back(texture);
            texture.loadFromFile("resources/textures/floor2.png");
            floor_textures.push_back(texture);
            texture.loadFromFile("resources/textures/ceiling1.png");
            ceil_textures.push_back(texture);
            texture.loadFromFile("resources/textures/ceiling2.png");
            ceil_textures.push_back(texture);
            texture.loadFromFile("resources/textures/sprites.png");
            sprite_textures.push_back(texture);
        };
};



#endif /* ASSETS_HPP */