#ifndef PIECES
#define PIECES
#define WHITE_PROMOTE 0
#define BLACK_PROMOTE 7
#define WHITE 1
#define BLACK 0
#define BOARD_SIZE 820
#define SIDESCREAN_SIZE 200
#define MARGIN 10.f
#define FIELD_SIZE 100.f

#include <SFML/graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>

class Piece {
    sf::Vector2i pos;
    int color;
    bool is_queen;

   public:
    sf::Vector2i get_pos();
    int get_color();
    bool get_is_queen();
    void set_pos(sf::Vector2i pos);
    // virtual bool move(Board& board, sf::Vector2i origin, sf::Vector2i destination) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    friend class Pawn;
    friend class Queen;
};

class Pawn : public Piece {
   public:
    Pawn(int x, int y);
    Pawn(int x, int y, int color);
    // bool move(Board& board, sf::Vector2i origin, sf::Vector2i destination);
    void draw(sf::RenderWindow& window);
};

class Queen : public Piece {
   public:
    Queen(int x, int y);
    Queen(sf::Vector2i pos);
    Queen(sf::Vector2i pos, int color);
    Queen(int x, int y, int color);
    // bool move(Board& board, sf::Vector2i origin, sf::Vector2i destination);
    void draw(sf::RenderWindow& window);
};

#endif