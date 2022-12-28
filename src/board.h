#ifndef BOARD
#define BOARD
#define WHITE_PROMOTE 8
#define BLACK_PROMOTE 1

#include "pieces.h"

class Board {
    int height, width;
    std::vector<std::unique_ptr<Piece>> pieces;

   public:
    Board(int dim);
    void draw(sf::RenderWindow& window);
    void add_piece(std::unique_ptr<Piece> piece);
    std::vector<std::unique_ptr<Piece>>& get_pieces();
    bool attempt_promote();
};

#endif