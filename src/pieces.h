#ifndef PIECES
#define PIECES
#define WHITE 1
#define BLACK 0
#define BOARD_SIZE 820
#define SIDESCREAN_SIZE 200
#define MARGIN 20.f
#define FIELD_SIZE 100.f

#include <SFML/graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>

class Piece {
    sf::Vector2f pos;
    int color;
    bool is_queen;

   public:
    sf::Vector2f get_pos();
    int get_color();
    void set_pos(sf::Vector2f pos);
    bool get_is_queen();
    virtual bool move(sf::Vector2f dest) { return false; };
    virtual void draw(sf::RenderWindow& window){};
    friend class Pawn;
    friend class Queen;
};

class Pawn : public Piece {
   public:
    Pawn(int x, int y);
    Pawn(int x, int y, int color);
    bool move(sf::Vector2f dest);
    void draw(sf::RenderWindow& window);
};

class Queen : public Piece {
   public:
    Queen(int x, int y);
    Queen(sf::Vector2f pos);
    bool move(sf::Vector2f dest);
    void draw(sf::RenderWindow& window);
};

#endif