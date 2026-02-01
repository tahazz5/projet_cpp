#pragma once

#include <string>
#include <vector>
#include "Move.h"


class Board {
public:
    Board();
    Piece* getPiece(int index) const;
    void setPiece(int index, Piece* piece);
    void removePiece(int index);
    void init();

    // Affichage console
    std::string toString() const;

    


private:
    Piece* squares[64]; 
};


