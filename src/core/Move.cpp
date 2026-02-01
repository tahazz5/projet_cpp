#include "Move.h"

Move::Move(Square f, Square t, PieceType p) : from(f), to(t), promotion(p) {}
Square Move::get_from() const { return from; }
Square Move::get_to() const { return to; }
PieceType Move::get_promotion() const { return promotion; }
std::string Move::to_string() const {
    std::string move_str = from.to_string() + to.to_string();
    if (promotion != PieceType::NONE) {
        switch (promotion) {
            case PieceType::QUEEN:
                move_str += "q";
                break;
            case PieceType::ROOK:
                move_str += "r";
                break;
            case PieceType::BISHOP:
                move_str += "b";
                break;
            case PieceType::KNIGHT:
                move_str += "n";
                break;
            default:
                break;
        }
    }
    return move_str;
}
