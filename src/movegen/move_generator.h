#pragma once

#include <vector>
#include "../core/move.h"

namespace chess {

class Board;

class MoveGenerator {
public:
    // Génère tous les coups pseudo-légaux (ne vérifie pas si le roi est en échec après le coup)
    static std::vector<Move> generate_pseudo_legal(const Board &b);

    // Filtre les coups pseudo-légaux pour ne garder que les coups légaux
    static std::vector<Move> generate_legal(const Board &b);
};

} // namespace chess
