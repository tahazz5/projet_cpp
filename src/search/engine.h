#pragma once

#include <cstdint>
#include "../core/move.h"

namespace chess {

struct SearchStats {
    int nodes = 0;
    int depth = 0;
};

class Board;

class Engine {
public:
    Engine();

    // Itérative deepening (retourne le meilleur coup trouvé)
    Move iterative_deepening(Board &b, int maxDepth, SearchStats &stats);

    // Recherche principale (negamax / alpha-beta)
    int negamax(Board &b, int depth, int alpha, int beta, SearchStats &stats);

    // Recherche quiescence (captures uniquement)
    int quiescence(Board &b, int alpha, int beta, SearchStats &stats);
};

} // namespace chess
