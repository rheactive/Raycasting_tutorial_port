#ifndef GAME_HPP // include guard
#define GAME_HPP

#include <sstream>
#include <iomanip>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "settings.hpp"
#include "map.hpp"
#include "player.hpp"
#include "wall_render.hpp"
#include "floor_render.hpp"
#include "assets.hpp"

// game context

class Game
{
public:
    sf::RenderWindow window;
    sf::Clock clock;
    float frame_time;
    float current_fps;
    sf::Font font;
    Assets assets;
    InputState input_state;
    Map map;
    std::vector<sf::RectangleShape> mini_map;
    Player player;
    std::vector<sf::CircleShape> mini_copy;
    sf::VertexArray map_rays;
    sf::VertexArray wall_quads;
    sf::VertexArray floor_quads;
    sf::VertexArray sky;

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
        sf::Clock clock;
        font.loadFromFile("resources/brohoney.ttf");
        Assets assets;
        InputState input_state;
        Map map;
        mini_map = map.mini_map();
        Player player;

        sky = update_sky();
    };

    void game_update()
    {
        // find FPS
        frame_time = clock.restart().asSeconds();
        current_fps = 1.0f / frame_time;

        InputState input_state;

        // general input parameters
        input_state.update();

        player.update(input_state, frame_time, map.walls);
        mini_copy = player.mini_copy();

        if (player.moved) {
            Raycast_floor raycast_floor (player);
            floor_quads = raycast_floor.draw_floor();
            Raycast_walls raycast_walls (player, map);
            map_rays = raycast_walls.map_rays();
            wall_quads = raycast_walls.draw_walls();
            sky = update_sky();
        };
    };

    void game_draw()
    {
        // fill screen with color
        window.clear(sf::Color(146, 226, 253, 255));

        // show sky
        window.draw(sky, &assets.back_textures[0]);

        // show floor
        window.draw(floor_quads, &assets.back_textures[1]);

        // show walls
        window.draw(wall_quads, &assets.wall_textures[0]);

        // show mini map
        draw_mini_map();

        // draw rays
        window.draw(map_rays);

        // show player on mini map
        draw_mini_copy();

        // show FPS
        std::ostringstream display_fps;
        display_fps << "FPS: " << std::fixed << std::setprecision(1) << current_fps;
        sf::Text text(display_fps.str(), font, 40);
        text.setFillColor(sf::Color::Black);
        text.setPosition(20.f, 20.f);
        window.draw(text);

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

    sf::VertexArray update_sky() {
        sf::VertexArray sky(sf::Quads, 8);

        sf::Vector2u tex_size = assets.back_textures[0].getSize();

        sky[0].position = sf::Vector2f(- WINDOW_WIDTH * player.angle / PI, HALF_HEIGHT * 1.0f);
        sky[1].position = sf::Vector2f(WINDOW_WIDTH * (2.01f - player.angle / PI), HALF_HEIGHT * 1.0f);
        sky[2].position = sf::Vector2f(WINDOW_WIDTH * (2.01f - player.angle / PI), 0.f);
        sky[3].position = sf::Vector2f(- WINDOW_WIDTH * player.angle / PI, 0.f);
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

        return(sky);
    };

};

#endif /* GAME_HPP */