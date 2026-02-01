#include "Board.h"
#include <iostream>



Board::Board() { init(); }

void Board::init() {
    for (int i = 0; i < 64; ++i) {
        squares[i] = nullptr;
    }
}
Piece* Board::getPiece(int index) const {
    if (index < 0 || index >= 64) return nullptr;
    return squares[index];
}
void Board::setPiece(int index, Piece* piece) {
    if(index < 0 || index >= 64) return;
    squares[index] = piece;
}
void Board::removePiece(int index) {
    if(index < 0 || index >= 64) return;
    squares[index] = 0;
}
std::string Board::toString() const {
    std::string boardStr;
    for (int rank = 7; rank >= 0; --rank) {
        for (int file = 0; file < 8; ++file) {
            int index = rank * 8 + file;
            Piece* piece = squares[index];
            if (piece) {
                boardStr += piece->to_string()[0]; // Just take the first letter of the piece type
            } else {
                boardStr += ".";
            }
            boardStr += " ";
        }
        boardStr += "\n";
    }
    return boardStr;
}