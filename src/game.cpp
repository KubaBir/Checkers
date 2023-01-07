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

sf::Vector2i game::coords_to_pos(sf::Event event) {
    sf::Vector2i coords(event.mouseButton.x, event.mouseButton.y);
    int x = coords.x;
    int y = coords.y;
    // std::cout << x << y << std::endl;
    return sf::Vector2i((x - MARGIN) / FIELD_SIZE, (y - MARGIN) / FIELD_SIZE);
}

bool game::attempt_move(Board& board, sf::Vector2i origin, sf::Vector2i destination) {
    if (!board.is_occupied(destination) && board.is_occupied(origin)) {
        if (abs(destination.x - origin.x) == 1 && abs(destination.y - origin.y) == 1)
            return game::move1(board, origin, destination);
        if (abs(destination.x - origin.x) == 2 && abs(destination.y - origin.y) == 2)
            return game::take(board, origin, destination);
    }

    return false;
}

bool game::move1(Board& board, sf::Vector2i origin, sf::Vector2i destination) {
    if (destination.y - origin.y > 0 && board.get_turn() == WHITE) return false;
    if (destination.y - origin.y < 0 && board.get_turn() == BLACK) return false;
    for (const auto& piece : board.get_pieces()) {
        if (piece->get_pos() == origin && piece->get_color() == board.get_turn()) {
            std::cout << "Moving from " << origin.x << " " << origin.y << " to " << destination.x << " " << destination.y << std::endl;
            piece->move(destination);
            board.switch_turn();
            return true;
        }
    }
    return false;
}

bool game::take(Board& board, sf::Vector2i origin, sf::Vector2i destination) {
    sf::Vector2i shift((destination.x - origin.x) / 2, (destination.y - origin.y) / 2);
    for (const auto& opponent : board.get_pieces()) {
        if (!(opponent->get_pos() == origin + shift && opponent->get_color() != board.get_turn())) continue;

        for (const auto& piece : board.get_pieces()) {
            if (piece->get_pos() == origin && piece->get_color() == board.get_turn()) {
                std::cout << "Moving from " << origin.x << " " << origin.y << " to " << destination.x << " " << destination.y << std::endl;
                piece->move(destination);
                board.remove_at(origin + shift);
                board.switch_turn();
                return true;
            }
        }
    }
    return false;
}

void game::update(Board& board) {
    board.attempt_promote();
}