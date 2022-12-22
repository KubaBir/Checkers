#ifndef PIECES
#define PIECES
#define WHITE 1
#define BLACK 0

#include <iostream>
#include <memory>
#include <vector>

struct position {
    int x, y;
};

class Piece {
    position pos;
    int color;
    bool is_queen;

   public:
    position get_pos();
    int get_color();
    void set_pos(position pos);
    bool get_is_queen();
    virtual bool move(position dest);
    friend class Pawn;
    friend class Queen;
};

class Pawn : public Piece {
   public:
    Pawn(int x, int y);
    Pawn(int x, int y, int color);
    bool move(position dest);
};

class Queen : public Piece {
   public:
    Queen(int x, int y);
    Queen(position pos);
    bool move(position dest);
};

#endif