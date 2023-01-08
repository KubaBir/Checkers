#include "pieces.h"

sf::Vector2i Piece::get_pos() { return this->pos; }
int Piece::get_color() { return this->color; }
bool Piece::get_is_queen() { return this->is_queen; }
void Piece::set_pos(sf::Vector2i pos) { this->pos = pos; }

Pawn::Pawn(int x, int y) {
    sf::Vector2i pos(x, y);
    this->pos = pos;
    this->is_queen = false;
}
Pawn::Pawn(int y, int x, int color) {
    sf::Vector2i pos(x, y);
    this->pos = pos;
    this->is_queen = false;
    this->color = color;
}
// bool Pawn::move(Board& board, sf::Vector2i origin, sf::Vector2i destination) {
//     if (!board.is_occupied(destination) && board.is_occupied(origin)) {
//         if (abs(destination.x - origin.x) == 1 && abs(destination.y - origin.y) == 1)
//             return game::move1(board, origin, destination);
//         if (abs(destination.x - origin.x) == 2 && abs(destination.y - origin.y) == 2)
//             return game::take_between(board, origin, destination);
//     }
// }
void Pawn::draw(sf::RenderWindow& window) {
    sf::CircleShape sprite(40);
    sprite.setOutlineColor(sf::Color(10, 10, 10));
    sprite.setOutlineThickness(2.);
    sprite.setOrigin(40., 40.);
    sprite.setPosition(sf::Vector2f(this->get_pos()) * FIELD_SIZE + sf::Vector2f(FIELD_SIZE / 2, FIELD_SIZE / 2) + sf::Vector2f(MARGIN, MARGIN));
    if (this->color == WHITE)
        sprite.setFillColor(sf::Color::White);
    else
        sprite.setFillColor(sf::Color::Black);
    window.draw(sprite);
}

Queen::Queen(int x, int y) {
    sf::Vector2i pos;
    pos.x = x;
    pos.y = y;
    this->pos = pos;
    this->is_queen = true;
}
Queen::Queen(sf::Vector2i pos) {
    this->pos = pos;
    this->is_queen = true;
}

Queen::Queen(sf::Vector2i pos, int color) {
    this->pos = pos;
    this->is_queen = true;
    this->color = color;
}

Queen::Queen(int y, int x, int color) {
    sf::Vector2i pos(x, y);
    this->pos = pos;
    this->is_queen = true;
    this->color = color;
}

// bool Queen::move(Board& board, sf::Vector2i origin, sf::Vector2i destination) {
//     return false;
// }
void Queen::draw(sf::RenderWindow& window) {
    sf::CircleShape sprite(40);
    sprite.setOutlineColor(sf::Color::Black);
    sprite.setOutlineThickness(1.);
    sprite.setOrigin(40., 40.);
    sprite.setPosition(sf::Vector2f(this->get_pos()) * FIELD_SIZE + sf::Vector2f(FIELD_SIZE / 2, FIELD_SIZE / 2) + sf::Vector2f(MARGIN, MARGIN));

    if (this->color == WHITE)
        sprite.setFillColor(sf::Color::Red);
    else
        sprite.setFillColor(sf::Color::Red);
    window.draw(sprite);
}
