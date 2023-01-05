#ifndef INPUT_HPP // include guard
#define INPUT_HPP

#include <map>

#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class InputState
{
public:
    std::map<std::string, bool> keys;

    InputState()
    {
        keys["W"] = false;
        keys["A"] = false;
        keys["S"] = false;
        keys["D"] = false;
        keys["Left"] = false;
        keys["Right"] = false;
        keys["Escape"] = false;
    };

    void update()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            keys["W"] = true;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            keys["A"] = true;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            keys["S"] = true;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            keys["D"] = true;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            keys["Left"] = true;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            keys["Right"] = true;
    };
};

#endif /* INPUT_HPP */