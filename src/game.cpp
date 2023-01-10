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
    board.add_piece(std::unique_ptr<Piece>(new Queen(2, 5, BLACK)));
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

// Convert mouse cooridnates to ingame field
sf::Vector2i game::coords_to_pos(sf::Event event) {
    sf::Vector2i coords(event.mouseButton.x, event.mouseButton.y);
    int x = coords.x;
    int y = coords.y;
    return sf::Vector2i((x - MARGIN) / FIELD_SIZE, (y - MARGIN) / FIELD_SIZE);
}

bool game::attempt_move(Board& board, sf::Vector2i origin, sf::Vector2i destination) {
    if (!board.is_occupied(origin) || board.is_occupied(destination)) return false;
    bool forced_take = false;
    if (!game::is_legal(board, origin, destination, forced_take)) return false;
    std::cout << "test";

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
    if (!(abs(destination.x - origin.x) == 1 && abs(destination.y - origin.y) == 1)) return false;
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

// Movie a piece with taking, and check for consecutive takes
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
                    if (move.front() == destination) {
                        turn_switch = false;
                        std::cout << "Chain take from " << move.front().x << move.front().y << std::endl;
                        board.set_is_chain_take(true);
                        board.set_chain_take_field(move.front());
                        break;
                    }
                }
                if (turn_switch)
                    board.switch_turn();
                return true;
            }
        }
    }
    return false;
}

// Board updates performed every move
void game::update(Board& board) {
    board.attempt_promote();
}

// Return a vector of forced moves
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
        const sf::Vector2i position = piece->get_pos();

        for (int i = 0; i < 4; i++) {
            if (!piece->get_is_queen()) {
                sf::Vector2i destination = position + 2 * shifts[i];
                if (destination.x < 0 || destination.x > 7) continue;
                if (destination.y < 0 || destination.y > 7) continue;
                if (!board.is_occupied(position + shifts[i], opponent)) continue;
                if (board.is_occupied(destination)) continue;
                moves.push_back(std::vector<sf::Vector2i>{sf::Vector2i(position), sf::Vector2i(destination)});
            } else {
                sf::Vector2i destination = position + shifts[i];
                while (destination.x < 7 && destination.x > 0 && destination.y < 7 && destination.y > 0) {
                    if (board.is_occupied(destination, opponent)) {
                        if (board.is_occupied(destination + shifts[i])) break;
                        moves.push_back(std::vector<sf::Vector2i>{sf::Vector2i(position), sf::Vector2i(destination + shifts[i])});
                        break;
                    } else if (board.is_occupied(destination))
                        break;
                    destination += shifts[i];
                }
            }
        }
    }
    return moves;
}

// Check if the move is inbounds and if taking is forced
bool game::is_legal(Board& board, sf::Vector2i origin, sf::Vector2i destination, bool& forced_take) {
    if (destination.x < 0 || destination.x > 7) return false;
    if (destination.y < 0 || destination.y > 7) return false;

    std::vector<std::vector<sf::Vector2i>> forced_moves = game::forced_moves(board, board.get_turn());
    if (forced_moves.size() != 0) {
        forced_take = true;
        std::vector<sf::Vector2i> attempted_move{origin, destination};
        bool correct = false;
        for (const auto& move : forced_moves) {
            if (move == attempted_move) {
                correct = true;
            } else
                std::cout << "Forced take from: " << move[0].x << " " << move[0].y << std::endl;
        }
        if (!correct) return false;
    }

    if (board.get_is_chain_take()) {
        if (origin != board.get_chain_take_field())
            return false;
        board.set_is_chain_take(false);
    }

    return true;
}

// Returns a list of all legal moves (only use if taking is not forced)
std::vector<std::vector<sf::Vector2i>> game::legal_moves(Board& board, int turn) {
    std::vector<std::vector<sf::Vector2i>> moves;
    sf::Vector2i all_shifts[4] = {
        sf::Vector2i(1, 1),
        sf::Vector2i(1, -1),
        sf::Vector2i(-1, 1),
        sf::Vector2i(-1, -1)};
    for (const auto& piece : board.get_pieces()) {
        if (piece->get_color() != board.get_turn()) continue;
        sf::Vector2i position = piece->get_pos();

        if (piece->get_is_queen()) {
            for (int i = 0; i < 4; i++) {
                sf::Vector2i destination = position + all_shifts[i];
                while (destination.x <= 7 && destination.x >= 0 && destination.y <= 7 && destination.y >= 0) {
                    if (!board.is_occupied(destination))
                        moves.push_back(std::vector<sf::Vector2i>{sf::Vector2i(position), sf::Vector2i(destination)});
                    else
                        break;
                    destination += all_shifts[i];
                }
            }
            continue;
        }
        sf::Vector2i shifts[2];
        if (piece->get_color() == WHITE) {
            shifts[0] = sf::Vector2i(1, -1);
            shifts[1] = sf::Vector2i(-1, -1);
        } else {
            shifts[0] = sf::Vector2i(1, 1);
            shifts[1] = sf::Vector2i(-1, 1);
        }
        for (int i = 0; i < 2; i++) {
            sf::Vector2i destination = position + shifts[i];
            if (destination.x < 0 || destination.x > 7) continue;
            if (destination.y < 0 || destination.y > 7) continue;
            if (!board.is_occupied(destination))
                moves.push_back(std::vector<sf::Vector2i>{sf::Vector2i(position), sf::Vector2i(destination)});
        }
    }
    return moves;
}

Board game::new_game(sf::RenderWindow& window) {
    std::cout << "Game over. Press any keyboard key to continue" << std::endl;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                Board board = game::setup();
                return board;
            }
        }
    }
}