#ifndef ASSETS_HPP // include guard
#define ASSETS_HPP

#include <vector>

#include <SFML/Graphics.hpp>

class Assets {
    public:
        std::vector<sf::Texture> wall_textures;
        std::vector<sf::Texture> back_textures;

        Assets () {
            sf::Texture texture;
            texture.loadFromFile("resources/textures/walls.png");
            wall_textures.push_back(texture);
            sf::Texture texture2;
            texture2.loadFromFile("resources/textures/sky.png");
            back_textures.push_back(texture2);
            texture2.loadFromFile("resources/textures/floor.png");
            back_textures.push_back(texture2);
        };
};



#endif /* ASSETS_HPP */