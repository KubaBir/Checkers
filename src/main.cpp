#include <SFML/graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>

#include "board.h"
#include "game.h"
#include "pieces.h"

using namespace std;

int main(int argc, char* argv[]) {
    // Board board;

    // board.add_piece(unique_ptr<Piece>(new Pawn(1, 8, WHITE)));
    // // board.add_piece(unique_ptr<Piece>(new Pawn(2, 7, WHITE)));
    // // board.add_piece(unique_ptr<Piece>(new Pawn(3, 7, WHITE)));
    // // board.add_piece(unique_ptr<Piece>(new Pawn(4, 7, WHITE)));

    // board.attempt_promote();
    // // board.get_pieces();
    // for (const auto& piece : board.get_pieces()) {
    //     cout << piece->get_is_queen() << piece->get_pos().x << endl;
    // }
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(BOARD_SIZE + SIDESCREAN_SIZE, BOARD_SIZE), "Checkers", sf::Style::Close, settings);

    Board board = game::setup();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();  // exit if window is closed

            // if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            // }
            // if (event.type == sf::Event::MouseButtonReleased && mousePressed) {
            // }
        }

        window.clear(sf::Color::Cyan);

        board.draw(window);
        // draw
        window.display();
    }

    return 0;
}