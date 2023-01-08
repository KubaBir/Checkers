#include "board.h"

Board::Board(int dim) {
    this->height = dim;
    this->width = dim;
    this->turn = WHITE;
}

void Board::add_piece(std::unique_ptr<Piece> piece) {
    this->pieces.push_back(std::move(piece));
}

void Board::switch_turn() {
    if (this->turn == WHITE)
        this->turn = BLACK;
    else
        this->turn = WHITE;
}

int Board::get_turn() {
    return this->turn;
}

std::vector<std::unique_ptr<Piece>>& Board::get_pieces() { return this->pieces; }

bool Board::is_occupied(sf::Vector2i field) {
    for (const auto& piece : this->get_pieces()) {
        if (piece->get_pos() == field)
            return true;
    }
    return false;
}

// Is the field occupied by a piece of *color
bool Board::is_occupied(sf::Vector2i field, int color) {
    for (const auto& piece : this->get_pieces()) {
        if (piece->get_pos() == field && piece->get_color() == color) {
            return true;
        }
    }
    return false;
}

void Board::draw(sf::RenderWindow& window) {
    sf::RectangleShape square(sf::Vector2f(99., 99.));
    square.setOutlineColor(sf::Color::Black);
    square.setOutlineThickness(1.);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            square.setPosition(sf::Vector2f(i * 100. + MARGIN, j * 100. + MARGIN));
            if ((i + j) % 2 == 0)
                square.setFillColor(sf::Color(220, 220, 220));
            else
                square.setFillColor(sf::Color(45, 45, 45));

            window.draw(square);
        }
    }
    for (const auto& piece : this->get_pieces()) {
        piece->draw(window);
    }
}

// Check for any available promotions
bool Board::attempt_promote() {
    auto id = this->pieces.begin();
    for (const auto& piece : this->get_pieces()) {
        if (((piece->get_color() == WHITE && piece->get_pos().y == WHITE_PROMOTE) || (piece->get_color() == BLACK && piece->get_pos().y == BLACK_PROMOTE)) && !piece->get_is_queen()) {
            sf::Vector2i temp_pos = piece->get_pos();
            int temp_color = piece->get_color();
            id = this->pieces.erase(id);
            this->add_piece(std::unique_ptr<Piece>(new Queen(temp_pos, temp_color)));
            std::cout << "Promote" << std::endl;
            return true;
        }
        id++;
    }

    return false;
}

bool Board::remove_at(sf::Vector2i position) {
    auto id = this->pieces.begin();
    for (const auto& piece : this->get_pieces()) {
        if (piece->get_pos() == position) {
            // std::cout << "Removing at " << position.x << " " << position.y << std::endl;
            this->pieces.erase(id);
            return true;
        }
        id++;
    }

    return false;
}

// Is the field occupied by a queen
bool Board::is_queen_at(sf::Vector2i position) {
    for (const auto& piece : this->get_pieces()) {
        if (piece->get_pos() == position) {
            if (piece->get_is_queen())
                return true;
            else
                return false;
        }
    }
    return false;
}
