#pragma once

#include <string>
#include "Board.h"


class Position {
private:
          
// facultatif plus tard :
    bool whiteCanCastleKingSide;
    bool whiteCanCastleQueenSide;
    bool blackCanCastleKingSide;
    bool blackCanCastleQueenSide;
    int enPassantSquare; // index de la case EP, -1 si aucune

    Board board; 
    

public:
    int halfMoveClock; 
    int sideToMove; 

    Position();
    Board getBoard() const;
    int getSideToMove() const;
    bool canWhiteCastleKingSide() const;
    bool canWhiteCastleQueenSide() const;
    bool canBlackCastleKingSide() const;
    bool canBlackCastleQueenSide() const;
    int getEnPassantSquare() const;
    int getHalfMoveClock() const;
    void setSideToMove(int c);
    int setHalfMoveClock(int hmc);
    std::string toString() const; // plateau + trait au move
    void makeMove(const Move& move);
    void undoMove(const Move& move, Piece* capturedPiece = nullptr);

};

