#include "pieces.h"

position Piece::get_pos() { return this->pos; }
int Piece::get_color() { return this->color; }
bool Piece::get_is_queen() { return this->is_queen; }
void Piece::set_pos(position pos) { this->pos = pos; }
bool Piece::move(position pos) { return false; }

Pawn::Pawn(int x, int y) {
    position pos;
    pos.x = x;
    pos.y = y;
    this->pos = pos;
    this->is_queen = false;
}
Pawn::Pawn(int x, int y, int color) {
    position pos;
    pos.x = x;
    pos.y = y;
    this->pos = pos;
    this->is_queen = false;
    this->color = color;
}
bool Pawn::move(position dest) {
    return false;
}

Queen::Queen(int x, int y) {
    position pos;
    pos.x = x;
    pos.y = y;
    this->pos = pos;
    this->is_queen = true;
}
Queen::Queen(position pos) {
    this->pos = pos;
    this->is_queen = true;
}
bool Queen::move(position dest) {
    return false;
}
