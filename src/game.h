#ifndef GAME
#define GAME

#include "board.h"

namespace game {
Board setup();
sf::Vector2i coords_to_pos(sf::Event event);
bool attempt_move(Board& board, sf::Vector2i origin, sf::Vector2i destination);
void update(Board& board);
bool move_pawn(Board& board, sf::Vector2i origin, sf::Vector2i destination);
bool move_queen(Board& board, sf::Vector2i origin, sf::Vector2i destination);
bool take_between(Board& board, sf::Vector2i origin, sf::Vector2i destination);
std::vector<std::vector<sf::Vector2i>> forced_moves(Board& board, int turn);
bool is_legal(Board& board, sf::Vector2i origin, sf::Vector2i destination, bool& forced_take);
std::vector<std::vector<sf::Vector2i>> legal_moves(Board& board, int turn);
Board new_game(sf::RenderWindow& window);
}  // namespace game

#endif