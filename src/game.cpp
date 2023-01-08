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
    board.add_piece(std::unique_ptr<Piece>(new Queen(5, 4, WHITE)));
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
    if (!board.is_occupied(origin) || board.is_occupied(destination)) return false;
    bool forced_take = false;
    if (!game::is_legal(board, origin, destination, forced_take)) return false;

    if (!forced_take) {
        if (board.is_queen_at(origin))
            return game::move_queen(board, origin, destination);
        else
            return game::move_pawn(board, origin, destination);
    }

    return game::take_between(board, origin, destination);
}

bool game::move_pawn(Board& board, sf::Vector2i origin, sf::Vector2i destination) {
    if (destination.y - origin.y > 0 && board.get_turn() == WHITE) return false;
    if (destination.y - origin.y < 0 && board.get_turn() == BLACK) return false;
    if (!(abs(destination.x - origin.x) == 1 || abs(destination.y - origin.y) == 1)) return false;
    for (const auto& piece : board.get_pieces()) {
        if (piece->get_pos() == origin && piece->get_color() == board.get_turn()) {
            std::cout << "Moving from " << origin.x << " " << origin.y << " to " << destination.x << " " << destination.y << std::endl;
            piece->set_pos(destination);

            board.switch_turn();
            return true;
        }
    }
    return false;
}

bool game::move_queen(Board& board, sf::Vector2i origin, sf::Vector2i destination) {
    sf::Vector2i shift((destination.x - origin.x) / abs(destination.x - origin.x), (destination.y - origin.y) / abs(destination.y - origin.y));
    sf::Vector2i field = origin + shift;
    while (field != destination) {
        if (board.is_occupied(field)) return false;
        field += shift;
    }
    for (const auto& piece : board.get_pieces()) {
        if (piece->get_pos() == origin && piece->get_color() == board.get_turn()) {
            std::cout << "Moving from " << origin.x << " " << origin.y << " to " << destination.x << " " << destination.y << std::endl;
            piece->set_pos(destination);
            board.switch_turn();
            return true;
        }
    }
    return false;
}

bool game::take_between(Board& board, sf::Vector2i origin, sf::Vector2i destination) {
    sf::Vector2i shift((destination.x - origin.x) / abs(destination.x - origin.x), (destination.y - origin.y) / abs(destination.y - origin.y));
    for (const auto& opponent : board.get_pieces()) {
        if (!(opponent->get_pos() == destination - shift && opponent->get_color() != board.get_turn())) continue;

        for (const auto& piece : board.get_pieces()) {
            if (piece->get_pos() == origin && piece->get_color() == board.get_turn()) {
                std::cout << "Taking from " << origin.x << " " << origin.y << " to " << destination.x << " " << destination.y << std::endl;
                piece->set_pos(destination);
                board.remove_at(destination - shift);

                bool turn_switch = true;
                std::vector<std::vector<sf::Vector2i>> moves = game::forced_moves(board, board.get_turn());
                for (const auto& move : moves) {
                    if (move.front() == destination) turn_switch = false;
                    std::cout << "Chain take from " << move.front().x << move.front().y << std::endl;
                }
                if (turn_switch)
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

std::vector<std::vector<sf::Vector2i>> game::forced_moves(Board& board, int turn) {
    std::vector<std::vector<sf::Vector2i>> moves;
    int opponent;
    if (board.get_turn() == WHITE)
        opponent = BLACK;
    else
        opponent = WHITE;
    sf::Vector2i shifts[4] = {
        sf::Vector2i(1, 1),
        sf::Vector2i(1, -1),
        sf::Vector2i(-1, 1),
        sf::Vector2i(-1, -1)};
    for (const auto& piece : board.get_pieces()) {
        if (piece->get_color() != board.get_turn()) continue;
        sf::Vector2i position = piece->get_pos();

        for (int i = 0; i < 4; i++) {
            if (!piece->get_is_queen()) {
                sf::Vector2i destination = position + 2 * shifts[i];
                if (destination.x < 0 || destination.x > 7) continue;
                if (destination.y < 0 || destination.y > 7) continue;
                if (!board.is_occupied(position + shifts[i], opponent)) continue;
                if (board.is_occupied(destination)) continue;
                std::cout << "Forced take at: " << (position + shifts[i]).x << (position + shifts[i]).y << std::endl;
                moves.push_back(std::vector<sf::Vector2i>{sf::Vector2i(position), sf::Vector2i(destination)});
            } else {
                sf::Vector2i destination = position;
                while (destination.x < 6 && destination.x > 1 && destination.y < 6 && destination.y > 1) {
                    destination += shifts[i];
                    if (board.is_occupied(destination, opponent)) {
                        if (board.is_occupied(destination + shifts[i])) break;
                        std::cout << "Forced take at: " << destination.x << " " << destination.y << std::endl;
                        moves.push_back(std::vector<sf::Vector2i>{sf::Vector2i(position), sf::Vector2i(destination + shifts[i])});
                        break;
                    }
                }
            }
        }
    }
    return moves;
}

bool game::is_legal(Board& board, sf::Vector2i origin, sf::Vector2i destination, bool& forced_take) {
    if (destination.x < 0 || destination.x > 7) return false;
    if (destination.y < 0 || destination.y > 7) return false;

    std::vector<std::vector<sf::Vector2i>> moves = game::forced_moves(board, board.get_turn());
    if (moves.size() != 0) {
        forced_take = true;
        std::vector<sf::Vector2i> attempted_move{origin, destination};
        bool correct = false;
        for (const auto& move : moves) {
            if (move == attempted_move) correct = true;
        }
        if (!correct) return false;
    }
    return true;
}