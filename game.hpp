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

// game context

class Game {
    public:
        sf::RenderWindow window;
        sf::Clock clock;
        float frame_time;
        float current_fps;
        sf::Font font;
        InputState input_state;
        Map map;
        std::vector<sf::RectangleShape> mini_map;
        Player player;
        std::vector<sf::CircleShape> mini_copy;

        Game() {
            // create the window
            window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), 
                WINDOW_TITLE, sf::Style::Default);
            window.setFramerateLimit(TARGET_FPS);

            window.setKeyRepeatEnabled(false);

            sf::Clock clock;

            font.loadFromFile("resources/brohoney.ttf");

            new_game();
        };

        void new_game() {
            InputState input_state;
            Map map;
            mini_map = map.mini_map();
            Player player;
        };

        void game_update() {
            // fill screen with color
            window.clear(sf::Color(115, 215, 255, 255));

            // find FPS
            frame_time = clock.restart().asSeconds();
            current_fps = 1.0f / frame_time;

            InputState input_state;

            // general input parameters
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                input_state.keys["W"] = true;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                input_state.keys["A"] = true;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                input_state.keys["S"] = true;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                input_state.keys["D"] = true;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                input_state.keys["Left"] = true;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                input_state.keys["Right"] = true;

            player.update(input_state, frame_time, map.walls);
            mini_copy = player.mini_copy();
        };

        void game_draw() {
            // show FPS
            std::ostringstream display_fps;
            display_fps << "FPS: " << std::fixed << std::setprecision(1) << current_fps;
            sf::Text text(display_fps.str(), font, 40);
	        text.setFillColor(sf::Color::Black);
	        text.setPosition(20.f, 20.f);
            window.draw(text);

            // show mini map
            draw_mini_map();

            // show player on mini map
            draw_mini_copy();

            // end the current frame
            window.display();
        };

        void game_check_events() {
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
				    if (event.key.code == sf::Keyboard::Escape) window.close();
			    };
            };
        };

        void game_run() {
            // run the program as long as the window is open
            while (window.isOpen()) {
                game_update();
                game_check_events();
                game_draw();
            }
        };

        void draw_mini_map () {

            for(int j = 0; j < mini_map.size(); j++) {
                window.draw(mini_map[j]);
            };

        };

        void draw_mini_copy () {

            for(int j = 0; j < mini_copy.size(); j++) {
                window.draw(mini_copy[j]);
            };

        };
};

#endif /* GAME_HPP */