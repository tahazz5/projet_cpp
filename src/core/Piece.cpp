#include "Piece.h"


Piece::Piece(PieceType t, int c) : type(t), color(c) {}

PieceType Piece::getType() const { return type; }
int Piece::getColor() const { return color; }

std::string Piece::to_string() const {
    switch(type) {
        case PieceType::NONE:   return ".";
        case PieceType::PAWN:   return "Pawn";
        case PieceType::KNIGHT: return "Knight";
        case PieceType::BISHOP: return "Bishop";
        case PieceType::ROOK:   return "Rook";
        case PieceType::QUEEN:  return "Queen";
        case PieceType::KING:   return "King";
    }
    return "Unknown"; // fallback
}
