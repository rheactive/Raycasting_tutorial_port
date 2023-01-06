#ifndef ASSETS_HPP // include guard
#define ASSETS_HPP

#include <vector>

#include <SFML/Graphics.hpp>

class Assets {
    public:
        std::vector<sf::Texture> wall_textures;
        std::vector<sf::Texture> back_textures;

        Assets () {
            // std::vector<sf::Texture> wall_textures;
            // std::vector<sf::Texture> back_textures;
            sf::Texture texture;
            texture.loadFromFile("resources/textures/floor.png");
            back_textures.push_back(texture);
            texture.loadFromFile("resources/textures/sky.png");
            back_textures.push_back(texture);
            texture.loadFromFile("resources/textures/1.png");
            wall_textures.push_back(texture);
            texture.loadFromFile("resources/textures/2.png");
            wall_textures.push_back(texture);
            texture.loadFromFile("resources/textures/3.png");
            wall_textures.push_back(texture);
            texture.loadFromFile("resources/textures/4.png");
            wall_textures.push_back(texture);
            wall_textures = wall_textures;
            back_textures = back_textures;
        };
};



#endif /* ASSETS_HPP */