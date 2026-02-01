#include "move_generator.h"
#include "../core/board.h"

using namespace chess;

std::vector<Move> MoveGenerator::generate_pseudo_legal(const Board &b) {
    // TODO: implémenter génération (pions, tours, cavaliers, fous, dames, roque, EP, promotions)
    (void)b;
    return {};
}

std::vector<Move> MoveGenerator::generate_legal(const Board &b) {
    // TODO: générer pseudo-légal puis filtrer par make/undo + in_check
    (void)b;
    return {};
}
