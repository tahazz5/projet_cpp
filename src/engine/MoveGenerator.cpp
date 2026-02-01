#include "MoveGenerator.h"
#include "../core/Board.h"

std::vector<Move> MoveGenerator::generateMoves(const Position& position) {
    std::vector<Move> moves;
    Board board = position.getBoard();
    int sideToMove = position.getSideToMove();

    auto makeMove = [](int from, int to) {
        return Move(Square(from), Square(to), PieceType::NONE);
    };

    for (int fromIndex = 0; fromIndex < 64; ++fromIndex) {
        Piece* piece = board.getPiece(fromIndex);
        if (!piece || piece->getColor() != sideToMove)
            continue;

        int rank = fromIndex / 8;
        int file = fromIndex % 8;

        switch (piece->getType()) {

        // ================== PAWN ==================
        case PieceType::PAWN: {
            int direction = (sideToMove == 0) ? 1 : -1;
            int startRank = (sideToMove == 0) ? 1 : 6;

            int oneStep = fromIndex + 8 * direction;
            if (oneStep >= 0 && oneStep < 64 && board.getPiece(oneStep) == nullptr) {
                moves.emplace_back(makeMove(fromIndex, oneStep));

                int twoStep = fromIndex + 16 * direction;
                if (rank == startRank && board.getPiece(twoStep) == nullptr) {
                    moves.emplace_back(makeMove(fromIndex, twoStep));
                }
            }

            // captures
            if (file > 0) {
                int captureLeft = fromIndex + 7 * direction;
                if (captureLeft >= 0 && captureLeft < 64) {
                    Piece* target = board.getPiece(captureLeft);
                    if (target && target->getColor() != sideToMove)
                        moves.emplace_back(makeMove(fromIndex, captureLeft));
                }
            }

            if (file < 7) {
                int captureRight = fromIndex + 9 * direction;
                if (captureRight >= 0 && captureRight < 64) {
                    Piece* target = board.getPiece(captureRight);
                    if (target && target->getColor() != sideToMove)
                        moves.emplace_back(makeMove(fromIndex, captureRight));
                }
            }
            break;
        }

        // ================== KNIGHT ==================
        case PieceType::KNIGHT: {
            const int offsets[8] = {-17, -15, -10, -6, 6, 10, 15, 17};
            for (int offset : offsets) {
                int to = fromIndex + offset;
                if (to < 0 || to >= 64)
                    continue;

                int toFile = to % 8;
                if (std::abs(toFile - file) > 2)
                    continue;

                Piece* target = board.getPiece(to);
                if (!target || target->getColor() != sideToMove)
                    moves.emplace_back(makeMove(fromIndex, to));
            }
            break;
        }

        // ================== BISHOP ==================
        case PieceType::BISHOP: {
            const int dirs[4] = {7, 9, -7, -9};
            for (int d : dirs) {
                int to = fromIndex;
                while (true) {
                    int prevFile = to % 8;
                    to += d;
                    if (to < 0 || to >= 64)
                        break;
                    if (std::abs((to % 8) - prevFile) != 1)
                        break;

                    Piece* target = board.getPiece(to);
                    if (!target) {
                        moves.emplace_back(makeMove(fromIndex, to));
                    } else {
                        if (target->getColor() != sideToMove)
                            moves.emplace_back(makeMove(fromIndex, to));
                        break;
                    }
                }
            }
            break;
        }

        // ================== ROOK ==================
        case PieceType::ROOK: {
            const int dirs[4] = {1, -1, 8, -8};
            for (int d : dirs) {
                int to = fromIndex;
                while (true) {
                    int prevFile = to % 8;
                    to += d;
                    if (to < 0 || to >= 64)
                        break;
                    if ((d == 1 || d == -1) && std::abs((to % 8) - prevFile) != 1)
                        break;

                    Piece* target = board.getPiece(to);
                    if (!target) {
                        moves.emplace_back(makeMove(fromIndex, to));
                    } else {
                        if (target->getColor() != sideToMove)
                            moves.emplace_back(makeMove(fromIndex, to));
                        break;
                    }
                }
            }
            break;
        }

        // ================== QUEEN ==================
        case PieceType::QUEEN: {
            const int dirs[8] = {1, -1, 8, -8, 7, 9, -7, -9};
            for (int d : dirs) {
                int to = fromIndex;
                while (true) {
                    int prevFile = to % 8;
                    to += d;
                    if (to < 0 || to >= 64)
                        break;
                    if (std::abs((to % 8) - prevFile) > 1 && (d == 1 || d == -1 || d == 7 || d == -7 || d == 9 || d == -9))
                        break;

                    Piece* target = board.getPiece(to);
                    if (!target) {
                        moves.emplace_back(makeMove(fromIndex, to));
                    } else {
                        if (target->getColor() != sideToMove)
                            moves.emplace_back(makeMove(fromIndex, to));
                        break;
                    }
                }
            }
            break;
        }

        // ================== KING ==================
        case PieceType::KING: {
            const int offsets[8] = {1, -1, 8, -8, 7, 9, -7, -9};
            for (int offset : offsets) {
                int to = fromIndex + offset;
                if (to < 0 || to >= 64)
                    continue;
                if (std::abs((to % 8) - file) > 1)
                    continue;

                Piece* target = board.getPiece(to);
                if (!target || target->getColor() != sideToMove)
                    moves.emplace_back(makeMove(fromIndex, to));
            }
            break;
        }

        default:
            break;
        }
    }

    return moves;
}
