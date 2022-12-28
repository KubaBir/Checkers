#include "pieces.h"

sf::Vector2f Piece::get_pos() { return this->pos; }
int Piece::get_color() { return this->color; }
bool Piece::get_is_queen() { return this->is_queen; }
void Piece::set_pos(sf::Vector2f pos) { this->pos = pos; }

Pawn::Pawn(int x, int y) {
    sf::Vector2f pos;
    pos.x = x;
    pos.y = y;
    this->pos = pos;
    this->is_queen = false;
}
Pawn::Pawn(int y, int x, int color) {
    sf::Vector2f pos;
    pos.x = x;
    pos.y = y;
    this->pos = pos;
    this->is_queen = false;
    this->color = color;
}
bool Pawn::move(sf::Vector2f dest) {
    return false;
}
void Pawn::draw(sf::RenderWindow& window) {
    sf::CircleShape sprite(40);
    sprite.setOutlineColor(sf::Color(10, 10, 10));
    sprite.setOutlineThickness(2.);
    sprite.setOrigin(40., 40.);
    sprite.setPosition(this->get_pos() * FIELD_SIZE + sf::Vector2f(40., 40.) + sf::Vector2f(MARGIN, MARGIN));
    if (this->color == WHITE)
        sprite.setFillColor(sf::Color::White);
    else
        sprite.setFillColor(sf::Color::Black);
    window.draw(sprite);
}

Queen::Queen(int x, int y) {
    sf::Vector2f pos;
    pos.x = x;
    pos.y = y;
    this->pos = pos;
    this->is_queen = true;
}
Queen::Queen(sf::Vector2f pos) {
    this->pos = pos;
    this->is_queen = true;
}
bool Queen::move(sf::Vector2f dest) {
    return false;
}
void Queen::draw(sf::RenderWindow& window) {
    sf::CircleShape sprite(40);
    sprite.setOutlineColor(sf::Color::Black);
    sprite.setOutlineThickness(1.);
    sprite.setOrigin(40., 40.);
    sprite.setPosition(this->get_pos());
    if (this->color == WHITE)
        sprite.setFillColor(sf::Color::White);
    else
        sprite.setFillColor(sf::Color::Black);
}
