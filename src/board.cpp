#include "board.h"

Board::Board(int dim) {
    this->height = dim;
    this->width = dim;
}
void Board::add_piece(std::unique_ptr<Piece> piece) {
    this->pieces.push_back(std::move(piece));
}

std::vector<std::unique_ptr<Piece>>& Board::get_pieces() { return this->pieces; }

void Board::draw(sf::RenderWindow& window) {
    sf::RectangleShape square(sf::Vector2f(99., 99.));
    square.setOutlineColor(sf::Color::Black);
    square.setOutlineThickness(1.);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            square.setPosition(sf::Vector2f(i * 100. + 10, j * 100. + 10));
            if ((i + j) % 2 == 0)
                square.setFillColor(sf::Color(200, 150, 0));
            else
                square.setFillColor(sf::Color(80, 41, 0));

            window.draw(square);
        }
    }
    for (const auto& piece : this->get_pieces()) {
        piece->draw(window);
    }
}

bool Board::attempt_promote() {
    // Tu cos nie dziala jak jest 1 albo 2 pionki xD
    auto id = this->pieces.begin();
    for (const auto& piece : this->get_pieces()) {
        if (piece->get_color() == WHITE && piece->get_pos().y == WHITE_PROMOTE) {
            sf::Vector2f temp = piece->get_pos();
            id = this->pieces.erase(id);
            this->pieces.push_back(std::unique_ptr<Queen>(new Queen(temp)));
            return true;
        }
        id++;
    }

    return false;
}