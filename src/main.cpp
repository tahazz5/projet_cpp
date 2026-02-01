#include <iostream>
#include "core/Piece.h"
#include "core/Board.h"
#include "core/Position.h"
#include "engine/MoveGenerator.h"

int main() {
    // 1️⃣ Initialiser la position
    Position pos;
    std::cout << "=== Plateau initial ===\n";
    std::cout << pos.toString() << std::endl;

    // 2️⃣ Générer tous les coups possibles
    auto moves = MoveGenerator::generateMoves(pos);
    std::cout << "=== Mouvements générés (" << moves.size() << ") ===\n";
    for (const auto& m : moves) {
        std::cout << m.to_string() << " ";
    }
    std::cout << "\n\n";

    // 3️⃣ Appliquer le premier coup
    if (!moves.empty()) {
        Move firstMove = moves[0];
        std::cout << "Appliquer le coup : " << firstMove.to_string() << std::endl;
        pos.makeMove(firstMove);

        std::cout << "=== Plateau après le coup ===\n";
        std::cout << pos.toString() << std::endl;
    }

    // 4️⃣ Générer les coups pour l'autre joueur
    auto moves2 = MoveGenerator::generateMoves(pos);
    std::cout << "=== Coups pour l'autre joueur (" << moves2.size() << ") ===\n";
    for (const auto& m : moves2) {
        std::cout << m.to_string() << " ";
    }
    std::cout << "\n\n";

    // 5️⃣ Test de undoMove (si implémenté)
    if (!moves.empty()) {
        Move firstMove = moves[0];
        Piece* captured = pos.getBoard().getPiece(firstMove.get_to().get_index());
        pos.undoMove(firstMove, captured);

        std::cout << "=== Plateau après undo ===\n";
        std::cout << pos.toString() << std::endl;
    }

    return 0;
}
