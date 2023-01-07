#include <SFML/graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>

#include "board.h"
#include "game.h"
#include "pieces.h"

using namespace std;

int main(int argc, char* argv[]) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(BOARD_SIZE + SIDESCREAN_SIZE, BOARD_SIZE), "Checkers", sf::Style::Close, settings);

    Board board = game::setup();

    sf::Vector2i origin;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();  // exit if window is closed

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                origin = game::coords_to_pos(event);
                // cout << "Origin: " << origin.x << " " << origin.y << endl;
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i destination = game::coords_to_pos(event);
                game::attempt_move(board, origin, destination);
                // cout << "Destination: " << destination.x << " " << destination.y << endl;
            }
        }
        // if (event.type == sf::Event::MouseButtonReleased && mousePressed) {
        // }
        game::update(board);
        window.clear(sf::Color::Cyan);

        board.draw(window);
        // draw
        window.display();
    }

    return 0;
}