#include <iostream>
#include <memory>
#include <vector>

#include "board.h"
#include "pieces.h"

using namespace std;

int main(int argc, char* argv[]) {
    Board board;

    board.add_piece(unique_ptr<Piece>(new Pawn(1, 8, WHITE)));
    // board.add_piece(unique_ptr<Piece>(new Pawn(2, 7, WHITE)));
    // board.add_piece(unique_ptr<Piece>(new Pawn(3, 7, WHITE)));
    // board.add_piece(unique_ptr<Piece>(new Pawn(4, 7, WHITE)));

    board.attempt_promote();
    // board.get_pieces();
    for (const auto& piece : board.get_pieces()) {
        cout << piece->get_is_queen() << piece->get_pos().x << endl;
    }

    return 0;
}