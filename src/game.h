#ifndef GAME
#define GAME

#include "board.h"
#include "pieces.h"

namespace game {
Board setup();
sf::Vector2i coords_to_pos(sf::Event event);
bool attempt_move(Board& board, sf::Vector2i origin, sf::Vector2i destination);
void update(Board& board);
bool move1(Board& board, sf::Vector2i origin, sf::Vector2i destination);
bool take(Board& board, sf::Vector2i origin, sf::Vector2i destination);
}  // namespace game

#endif