#pragma once

#include <string>
#include "Piece.h"
#include "Square.h"
class Move{
    private:
    Square from;          // case de départ
    Square to;              // case d'arrivée
    PieceType promotion;
    public:
    Move(Square f, Square t, PieceType p ) ;
    Square get_from() const ;
    Square get_to() const ;
    PieceType get_promotion() const ;
    std::string to_string() const ;
};