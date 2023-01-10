#include <SFML/graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>

// #include "board.h"
#include "game.h"
// #include "pieces.h"

using namespace std;

int main(int argc, char* argv[]) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(BOARD_SIZE + SIDESCREAN_SIZE, BOARD_SIZE), "Checkers", sf::Style::Close, settings);
    bool game_end = false;

    Board board = game::setup();

    sf::Vector2i origin;
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                origin = game::coords_to_pos(event);
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i destination = game::coords_to_pos(event);
                if (game::attempt_move(board, origin, destination)) {
                    cout << "----------" << endl;

                    if (game::forced_moves(board, board.get_turn()).size() == 0) {
                        std::vector<std::vector<sf::Vector2i>> moves = game::legal_moves(board, board.get_turn());
                        if (moves.size() == 0) game_end = true;
                    }
                }
                game::update(board);
            }
        }

        window.clear(sf::Color::Cyan);
        board.draw(window);
        window.display();
        if (game_end) {
            board = game::new_game(window);
            game_end = false;
        }
    }

    return 0;
}