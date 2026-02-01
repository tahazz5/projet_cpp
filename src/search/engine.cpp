#include "engine.h"
#include "../core/board.h"
#include "../movegen/move_generator.h"

using namespace chess;

Engine::Engine() {}

Move Engine::iterative_deepening(Board &b, int maxDepth, SearchStats &stats) {
    (void)b; (void)maxDepth; (void)stats;
    // TODO: iterative deepening + aspitation windows + time
    return Move{};
}

int Engine::negamax(Board &b, int depth, int alpha, int beta, SearchStats &stats) {
    (void)b; (void)depth; (void)alpha; (void)beta; (void)stats;
    // TODO: implementer negamax avec move ordering et transposition table
    return 0;
}

int Engine::quiescence(Board &b, int alpha, int beta, SearchStats &stats) {
    (void)b; (void)alpha; (void)beta; (void)stats;
    // TODO: implementer qsearch
    return 0;
}
