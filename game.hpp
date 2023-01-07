#ifndef GAME_HPP // include guard
#define GAME_HPP

#include <sstream>
#include <iomanip>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "settings.hpp"
#include "map.hpp"
#include "player.hpp"
#include "wall_render.hpp"
#include "floor_render.hpp"
#include "assets.hpp"
#include "sprites.hpp"

// game context

class Game
{
public:
    sf::RenderWindow window;
    sf::Clock clock1;
    sf::Clock clock2;
    float current_time;
    float frame_time;
    int frame_count;
    int seconds_count;
    int minutes_count;
    int current_fps;
    sf::Font font;
    Assets assets;
    InputState input_state;
    Map map = Map(1);
    std::vector<sf::RectangleShape> mini_map;
    Player player;
    std::vector<sf::CircleShape> mini_copy;
    sf::VertexArray map_rays;
    sf::VertexArray wall_quads;
    sf::VertexArray floor_quads;
    sf::VertexArray ceil_quads;
    sf::VertexArray sky;
    std::vector<sf::VertexArray> sprite_quads;

    Game()
    {
        // create the window
        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                      WINDOW_TITLE, sf::Style::Default);
        window.setFramerateLimit(TARGET_FPS);
        window.setKeyRepeatEnabled(false);

        new_game();
    };

    void new_game()
    {
        font.loadFromFile("resources/brohoney.ttf");

        mini_map = map.mini_map();

        sky = update_sky();

        clock1.restart();
        clock2.restart();

        current_fps = TARGET_FPS;

        frame_count = 0;
        seconds_count = 0;
        minutes_count = 0;

        Raycast_floor raycast_floor(player);
        floor_quads = raycast_floor.draw_floor();
        ceil_quads = raycast_floor.draw_ceiling();
        Raycast_walls raycast_walls(player, map);
        map_rays = raycast_walls.map_rays();
        wall_quads = raycast_walls.draw_walls();
        Sprites sprites(1, map, player);
        sprite_quads = sprites.draw_sprites(raycast_walls.rays);
    };

    void game_update()
    {
        // find FPS and time
        update_time();

        InputState input_state;

        // general input parameters
        input_state.update();

        player.update(input_state, frame_time, map);
        mini_copy = player.mini_copy();

        if (player.moved)
        {
            map = Map(player.map_id);
            mini_map = map.mini_map();
            Raycast_floor raycast_floor(player);
            floor_quads = raycast_floor.draw_floor();
            ceil_quads = raycast_floor.draw_ceiling();
            Raycast_walls raycast_walls(player, map);
            map_rays = raycast_walls.map_rays();
            wall_quads = raycast_walls.draw_walls();
            sky = update_sky();
            Sprites sprites(1, map, player);
            sprite_quads = sprites.draw_sprites(raycast_walls.rays);
        };
    };

    void game_draw()
    {
        // fill screen with color
        window.clear(sf::Color(146, 226, 253, 255));

        // show sky
        window.draw(sky, &assets.sky_textures[0]);

        // show ceiling
        window.draw(ceil_quads, &assets.ceil_textures[player.map_id - 1]);

        // show floor
        window.draw(floor_quads, &assets.floor_textures[player.map_id - 1]);

        // show walls
        window.draw(wall_quads, &assets.wall_textures[0]);

        // show sprites
        show_sprites();

        // show mini map
        draw_mini_map();

        // draw rays
        window.draw(map_rays);

        // show player on mini map
        draw_mini_copy();

        // show FPS and time
        show_time();

        // end the current frame
        window.display();
    };

    void game_check_events()
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                // close at the press of Esc button
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            };
        };
    };

    void game_run()
    {
        // run the program as long as the window is open
        while (window.isOpen())
        {
            game_update();
            game_check_events();
            game_draw();
        }
    };

    void draw_mini_map()
    {

        for (int j = 0; j < mini_map.size(); j++)
        {
            window.draw(mini_map[j]);
        };
    };

    void draw_mini_copy()
    {

        for (int j = 0; j < 1; j++)
        {
            window.draw(mini_copy[j]);
        };
    };

    void show_sprites()
    {
        for (int j = 0; j < sprite_quads.size(); j++)
        {
            window.draw(sprite_quads[j], &assets.sprite_textures[0]);
        };
    };

    sf::VertexArray update_sky()
    {
        sf::VertexArray sky(sf::Quads, 8);

        sf::Vector2u tex_size = assets.sky_textures[0].getSize();

        sky[0].position = sf::Vector2f(-WINDOW_WIDTH * player.angle / PI, HALF_HEIGHT * 1.0f);
        sky[1].position = sf::Vector2f(WINDOW_WIDTH * (2.01f - player.angle / PI), HALF_HEIGHT * 1.0f);
        sky[2].position = sf::Vector2f(WINDOW_WIDTH * (2.01f - player.angle / PI), 0.f);
        sky[3].position = sf::Vector2f(-WINDOW_WIDTH * player.angle / PI, 0.f);
        sky[4].position = sf::Vector2f(WINDOW_WIDTH * (2.01f - player.angle / PI), HALF_HEIGHT * 1.0f);
        sky[5].position = sf::Vector2f(WINDOW_WIDTH * (4.01f - player.angle / PI), HALF_HEIGHT * 1.0f);
        sky[6].position = sf::Vector2f(WINDOW_WIDTH * (4.01f - player.angle / PI), 0.f);
        sky[7].position = sf::Vector2f(WINDOW_WIDTH * (2.01f - player.angle / PI), 0.f);

        sky[0].texCoords = sf::Vector2f(0.f, tex_size.y * 1.0f);
        sky[1].texCoords = sf::Vector2f(tex_size.x * 1.0f, tex_size.y * 1.0f);
        sky[2].texCoords = sf::Vector2f(tex_size.x * 1.0f, 0.f);
        sky[3].texCoords = sf::Vector2f(0.f, 0.f);
        sky[4].texCoords = sf::Vector2f(0.f, tex_size.y * 1.0f);
        sky[5].texCoords = sf::Vector2f(tex_size.x * 1.0f, tex_size.y * 1.0f);
        sky[6].texCoords = sf::Vector2f(tex_size.x * 1.0f, 0.f);
        sky[7].texCoords = sf::Vector2f(0.f, 0.f);

        return (sky);
    };

    void update_time()
    {
        current_time = clock1.getElapsedTime().asSeconds();
        frame_time = clock2.restart().asSeconds();

        frame_count += 1;

        if (current_time >= 1.0)
        {
            seconds_count += 1;
            current_fps = frame_count;
            frame_count = 0;
            clock1.restart();
        };

        if (seconds_count >= 60)
        {
            minutes_count += 1;
            seconds_count = 0;
        };
    };

    void show_time()
    {
        sf::RectangleShape text_bg;
        text_bg.setSize(sf::Vector2f(230, 100));
        text_bg.setPosition(sf::Vector2f(15, 15));
        text_bg.setFillColor(sf::Color(150, 150, 150, 255));
        text_bg.setOutlineThickness(5.f);
        text_bg.setOutlineColor(sf::Color(50, 50, 50, 255));
        window.draw(text_bg);

        std::ostringstream display_fps;
        display_fps << "FPS: " << current_fps;
        sf::Text text(display_fps.str(), font, 40);
        text.setFillColor(sf::Color::Black);
        text.setPosition(30.f, 20.f);
        text.setOrigin(0.f, 0.f);
        window.draw(text);
        std::ostringstream display_time;
        display_time << "Time: " << minutes_count << ":" << seconds_count;
        text = sf::Text(display_time.str(), font, 40);
        text.setFillColor(sf::Color::Black);
        text.setPosition(30.f, 60.f);
        text.setOrigin(0.f, 0.f);
        window.draw(text);
    };
};

#endif /* GAME_HPP */