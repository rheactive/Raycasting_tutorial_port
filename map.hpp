#ifndef MAP_HPP // include guard
#define MAP_HPP

#include <vector>
#include <tuple>
#include <map>

#include <SFML/Graphics.hpp>

#include "settings.hpp"

// define the map(s)
const int map1_walls[MAP_HEIGHT][MAP_WIDTH] =
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
     1, 0, 0, 2, 2, 2, 2, 0, 0, 0, 3, 3, 3, 0, 0, 1,
     1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 3, 0, 0, 1,
     1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 3, 0, 0, 1,
     1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1,
     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5,
     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 1,
     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 0, 0, 1,
     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
     1, 0, 0, 0, 4, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 1,
     1, 0, 0, 0, 4, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 1,
     1, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
     1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

const int map1_sprites[MAP_HEIGHT][MAP_WIDTH] =
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const int map2_walls[MAP_HEIGHT][MAP_WIDTH] =
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5,
     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
     1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

// map

class MapElement {
    public:
        int tex_id;
        float x;
        float y;
};

class Map
{
public:
    int map_id;
    std::map<int, MapElement> walls;
    std::map<int, MapElement> sprites;

    Map (int map_id)
    {
        if (map_id == 1)
        {
            for (int x = 0; x < MAP_WIDTH; x++)
        {
            for (int y = 0; y < MAP_HEIGHT; y++)
            {
                if (map1_walls[y][x] > 0)
                {
                    int tile = y * MAP_WIDTH + x + 1;
                    walls[tile].tex_id = map1_walls[y][x];
                    walls[tile].x = x;
                    walls[tile].y = y;
                };
                if (map1_sprites[y][x] > 0)
                {
                    int tile = y * MAP_WIDTH + x + 1;
                    sprites[tile].tex_id = map1_sprites[y][x];
                    sprites[tile].x = x + 0.5;
                    sprites[tile].y = y + 0.5;
                }
            }
        }
        }
        else if (map_id == 2)
        {
            for (int x = 0; x < MAP_WIDTH; x++)
        {
            for (int y = 0; y < MAP_HEIGHT; y++)
            {
                if (map2_walls[y][x] > 0)
                {
                    int tile = y * MAP_WIDTH + x + 1;
                    walls[tile].tex_id = map1_walls[y][x];
                    walls[tile].x = x;
                    walls[tile].y = y;
                }
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
        whole_map.setOutlineThickness(0.f);

        to_draw.push_back(whole_map);

        for (auto const &w : walls)
        {
            sf::RectangleShape tile;
            tile.setSize(sf::Vector2f(TILE_WIDTH, TILE_HEIGHT));
            tile.setPosition(sf::Vector2f(MINI_MAP_X + w.second.x * TILE_WIDTH,
                                          MINI_MAP_Y + w.second.y * TILE_HEIGHT));
            tile.setFillColor(sf::Color(50, 50, 50, 255));
            whole_map.setOutlineThickness(0.f);

            to_draw.push_back(tile);
        }

        return (to_draw);
    };
};

#endif /* MAP_HPP */