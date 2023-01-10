#ifndef BOARD
#define BOARD

#include <SFML/graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>

#include "pieces.h"

class Board {
    int height, width;
    int turn;
    std::vector<std::unique_ptr<Piece>> pieces;
    bool is_chain_take;
    sf::Vector2i chain_take_field;

   public:
    Board(int dim);
    void switch_turn();
    int get_turn();
    bool get_is_chain_take();
    void set_is_chain_take(bool val);
    sf::Vector2i get_chain_take_field();
    void set_chain_take_field(sf::Vector2i position);

    void draw(sf::RenderWindow& window);
    void add_piece(std::unique_ptr<Piece> piece);
    std::vector<std::unique_ptr<Piece>>& get_pieces();
    bool attempt_promote();
    bool is_occupied(sf::Vector2i field);
    bool is_occupied(sf::Vector2i field, int color);
    bool remove_at(sf::Vector2i position);
    bool is_queen_at(sf::Vector2i position);
};

#endif