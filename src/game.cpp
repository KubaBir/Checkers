#include "game.h"

#include <SFML/graphics.hpp>

Board game::setup() {
    Board board(BOARD_SIZE);
    board.add_piece(std::unique_ptr<Piece>(new Pawn(0, 1, BLACK)));
    board.add_piece(std::unique_ptr<Piece>(new Pawn(0, 3, BLACK)));
    board.add_piece(std::unique_ptr<Piece>(new Pawn(0, 5, BLACK)));
    board.add_piece(std::unique_ptr<Piece>(new Pawn(0, 7, BLACK)));
    board.add_piece(std::unique_ptr<Piece>(new Pawn(1, 0, BLACK)));
    board.add_piece(std::unique_ptr<Piece>(new Pawn(1, 2, BLACK)));
    board.add_piece(std::unique_ptr<Piece>(new Pawn(1, 4, BLACK)));
    board.add_piece(std::unique_ptr<Piece>(new Pawn(1, 6, BLACK)));
    board.add_piece(std::unique_ptr<Piece>(new Pawn(2, 1, BLACK)));
    board.add_piece(std::unique_ptr<Piece>(new Pawn(2, 3, BLACK)));
    board.add_piece(std::unique_ptr<Piece>(new Pawn(2, 5, BLACK)));
    board.add_piece(std::unique_ptr<Piece>(new Pawn(2, 7, BLACK)));

    board.add_piece(std::unique_ptr<Piece>(new Pawn(7, 0, WHITE)));
    board.add_piece(std::unique_ptr<Piece>(new Pawn(7, 2, WHITE)));
    board.add_piece(std::unique_ptr<Piece>(new Pawn(7, 4, WHITE)));
    board.add_piece(std::unique_ptr<Piece>(new Pawn(7, 6, WHITE)));
    board.add_piece(std::unique_ptr<Piece>(new Pawn(6, 1, WHITE)));
    board.add_piece(std::unique_ptr<Piece>(new Pawn(6, 3, WHITE)));
    board.add_piece(std::unique_ptr<Piece>(new Pawn(6, 5, WHITE)));
    board.add_piece(std::unique_ptr<Piece>(new Pawn(6, 7, WHITE)));
    board.add_piece(std::unique_ptr<Piece>(new Pawn(5, 0, WHITE)));
    board.add_piece(std::unique_ptr<Piece>(new Pawn(5, 2, WHITE)));
    board.add_piece(std::unique_ptr<Piece>(new Pawn(5, 4, WHITE)));
    board.add_piece(std::unique_ptr<Piece>(new Pawn(5, 6, WHITE)));

    return board;
}