#include "board.h"

void Board::add_piece(std::unique_ptr<Piece> piece) {
    this->pieces.push_back(std::move(piece));
}
std::vector<std::unique_ptr<Piece>>& Board::get_pieces() { return this->pieces; }
void Board::draw() {}
bool Board::attempt_promote() {
    // Tu cos nie dziala jak jest 1 albo 2 pionki xD
    auto id = this->pieces.begin();
    for (const auto& piece : this->pieces) {
        if (piece->get_color() == WHITE && piece->get_pos().y == WHITE_PROMOTE) {
            position temp = piece->get_pos();
            id = this->pieces.erase(id);
            this->pieces.push_back(std::unique_ptr<Queen>(new Queen(temp)));
            return true;
        }
        id++;
    }

    return false;
}