#include "Position.h"

Position::Position()
    : sideToMove(0),
      whiteCanCastleKingSide(true),
      whiteCanCastleQueenSide(true),
      blackCanCastleKingSide(true),
      blackCanCastleQueenSide(true),
      enPassantSquare(-1),
      halfMoveClock(0) 
      {
        for (int i = 0; i < 64; ++i) {
        board.setPiece(i, nullptr);
        }

        for (int file = 0; file < 8; ++file) {
        board.setPiece(8 + file, new Piece(PieceType::PAWN,0));   // rangée 2
        board.setPiece(48 + file, new Piece(PieceType::PAWN, 1));  // rangée 7
        }
         
        board.setPiece(3, new Piece(PieceType::QUEEN, 0));
        board.setPiece(59, new Piece(PieceType::QUEEN, 1));

    
        board.setPiece(4, new Piece(PieceType::KING, 0));
        board.setPiece(60, new Piece(PieceType::KING, 1));

        board.setPiece(0, new Piece(PieceType::ROOK, 0));
        board.setPiece(7, new Piece(PieceType::ROOK, 1));
        board.setPiece(56, new Piece(PieceType::ROOK, 0));
        board.setPiece(63, new Piece(PieceType::ROOK, 1));

    
        board.setPiece(1, new Piece(PieceType::KNIGHT, 0));
        board.setPiece(6, new Piece(PieceType::KNIGHT, 1));
        board.setPiece(57, new Piece(PieceType::KNIGHT, 0));
        board.setPiece(62, new Piece(PieceType::KNIGHT, 1));

        board.setPiece(2, new Piece(PieceType::BISHOP, 0));
        board.setPiece(5, new Piece(PieceType::BISHOP, 1));
        board.setPiece(58, new Piece(PieceType::BISHOP, 0));
        board.setPiece(61, new Piece(PieceType::BISHOP, 1));

      }
Board Position::getBoard() const { return board; }
int Position::getSideToMove() const { return sideToMove; }
bool Position::canWhiteCastleKingSide() const { return whiteCanCastleKingSide; }
bool Position::canWhiteCastleQueenSide() const { return whiteCanCastleQueenSide; }
bool Position::canBlackCastleKingSide() const { return blackCanCastleKingSide; }
bool Position::canBlackCastleQueenSide() const { return blackCanCastleQueenSide; }
int Position::getEnPassantSquare() const { return enPassantSquare; }
int Position::getHalfMoveClock() const { return halfMoveClock; }
void Position::setSideToMove(int c) { sideToMove = c; }
std::string Position::toString() const {
    std::string posStr = board.toString();
    posStr += (sideToMove == 0) ? "White to move\n" : "Black to move\n";
    return posStr;
}

void Position::makeMove(const Move& move) {
    int fromIndex = move.get_from().get_index();
    int toIndex   = move.get_to().get_index();

    Piece* movingPiece = board.getPiece(fromIndex);
    if (!movingPiece)
        return; // sécurité minimale

    // Gérer la capture
    Piece* capturedPiece = board.getPiece(toIndex);
    if (capturedPiece) {
        board.removePiece(toIndex); // delete ou nullptr selon ton design
        halfMoveClock = 0;           // reset si capture
    } else {
        halfMoveClock++;
    }

    // Déplacer la pièce
    board.setPiece(toIndex, movingPiece);
    board.removePiece(fromIndex);

    // Changer le joueur au trait
    sideToMove = 1 - sideToMove;
}

void Position::undoMove(const Move& move, Piece* capturedPiece) {
    int fromIndex = move.get_from().get_index();
    int toIndex   = move.get_to().get_index();

    Piece* movingPiece = board.getPiece(toIndex);
    if (!movingPiece)
        return; // sécurité minimale

    // Replacer la pièce déplacée
    board.setPiece(fromIndex, movingPiece);
    board.removePiece(toIndex);

    // Replacer la pièce capturée si elle existe
    if (capturedPiece) {
        board.setPiece(toIndex, capturedPiece);
    }

    // Changer le joueur au trait
    sideToMove = 1 - sideToMove;
}
