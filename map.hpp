#ifndef MAP_HPP // include guard
#define MAP_HPP

#include <vector>
#include <map>

#include <SFML/Graphics.hpp>

#include "settings.hpp"

// define the map(s)
const int map_walls[MAP_HEIGHT][MAP_WIDTH] =
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
     1, 0, 0, 2, 2, 2, 2, 0, 0, 0, 3, 3, 3, 0, 0, 1,
     1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 3, 0, 0, 1,
     1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 3, 0, 0, 1,
     1, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1,
     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 1,
     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 1,
     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 0, 0, 1,
     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
     1, 0, 0, 0, 4, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 1,
     1, 0, 0, 0, 4, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 1,
     1, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
     1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

// map

class Map
{
public:
    std::map<int, int> walls;
    std::vector<int> walls_x;
    std::vector<int> walls_y;

    Map()
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            for (int y = 0; y < MAP_HEIGHT; y++)
            {
                if (map_walls[y][x] > 0)
                {
                    int tile = y * MAP_WIDTH + x + 1;
                    walls[tile] = map_walls[y][x];
                    walls_x.push_back(x);
                    walls_y.push_back(y);
                }
            }
        }
    };

    std::vector<sf::RectangleShape> mini_map()
    {
        std::vector<sf::RectangleShape> to_draw;

        sf::RectangleShape whole_map;
        whole_map.setSize(sf::Vector2f(MINI_MAP_WIDTH, MINI_MAP_HEIGHT));
        whole_map.setPosition(sf::Vector2f(MINI_MAP_X, MINI_MAP_Y));
        whole_map.setFillColor(sf::Color(150, 150, 150, 255));

        to_draw.push_back(whole_map);

        for (int w = 0; w < walls.size(); w++)
        {
            sf::RectangleShape tile;
            tile.setSize(sf::Vector2f(TILE_WIDTH, TILE_HEIGHT));
            tile.setPosition(sf::Vector2f(MINI_MAP_X + walls_x[w] * TILE_WIDTH,
                                          MINI_MAP_Y + walls_y[w] * TILE_HEIGHT));
            tile.setFillColor(sf::Color(50, 50, 50, 255));
            tile.setOutlineColor(sf::Color(255, 255, 255, 255));

            to_draw.push_back(tile);
        }

        return (to_draw);
    };
};

#endif /* MAP_HPP */