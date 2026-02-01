#pragma once
#include <string>


enum struct PieceType {
    NONE,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};
class Piece {
private:
    PieceType type;
    int color; // 0 = white, 1 = black
public:
    Piece(PieceType t, int c);
    PieceType getType() const;
    int getColor() const;
    std::string to_string() const;
};






