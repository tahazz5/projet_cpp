#include "SimpleAI.h"
#include "MoveGenerator.h"
#include <algorithm>
#include <limits>

namespace {

int pieceValue(PieceType type) {
    switch (type) {
    case PieceType::PAWN:
        return 100;
    case PieceType::KNIGHT:
        return 320;
    case PieceType::BISHOP:
        return 330;
    case PieceType::ROOK:
        return 500;
    case PieceType::QUEEN:
        return 900;
    case PieceType::KING:
        return 0;
    default:
        return 0;
    }
}

} // namespace

SimpleAI::SimpleAI(int depth) : maxDepth(std::max(1, depth)) {}

int SimpleAI::evaluate(const Position &position) const {
    const Board board = position.getBoard();
    int score = 0;
    for (int index = 0; index < 64; ++index) {
        Piece *piece = board.getPiece(index);
        if (!piece) {
            continue;
        }
        int value = pieceValue(piece->getType());
        score += (piece->getColor() == 0) ? value : -value;
    }
    return score;
}

int SimpleAI::minimax(Position &position, int depth, int alpha, int beta) const {
    if (depth == 0) {
        return evaluate(position);
    }

    auto moves = MoveGenerator::generateMoves(position);
    if (moves.empty()) {
        return evaluate(position);
    }

    int sideToMove = position.getSideToMove();
    if (sideToMove == 0) {
        int best = std::numeric_limits<int>::min();
        for (const auto &move : moves) {
            Piece *captured = position.getBoard().getPiece(move.get_to().get_index());
            position.makeMove(move);
            int score = minimax(position, depth - 1, alpha, beta);
            position.undoMove(move, captured);
            best = std::max(best, score);
            alpha = std::max(alpha, best);
            if (beta <= alpha) {
                break;
            }
        }
        return best;
    }

    int best = std::numeric_limits<int>::max();
    for (const auto &move : moves) {
        Piece *captured = position.getBoard().getPiece(move.get_to().get_index());
        position.makeMove(move);
        int score = minimax(position, depth - 1, alpha, beta);
        position.undoMove(move, captured);
        best = std::min(best, score);
        beta = std::min(beta, best);
        if (beta <= alpha) {
            break;
        }
    }
    return best;
}

Move SimpleAI::chooseMove(Position &position) {
    auto moves = MoveGenerator::generateMoves(position);
    if (moves.empty()) {
        return Move(Square(0), Square(0), PieceType::NONE);
    }

    int sideToMove = position.getSideToMove();
    Move bestMove = moves.front();
    int bestScore = (sideToMove == 0) ? std::numeric_limits<int>::min()
                                      : std::numeric_limits<int>::max();

    for (const auto &move : moves) {
        Piece *captured = position.getBoard().getPiece(move.get_to().get_index());
        position.makeMove(move);
        int score = minimax(position, maxDepth - 1, std::numeric_limits<int>::min(),
                            std::numeric_limits<int>::max());
        position.undoMove(move, captured);

        if ((sideToMove == 0 && score > bestScore) || (sideToMove == 1 && score < bestScore)) {
            bestScore = score;
            bestMove = move;
        }
    }

    return bestMove;
}
