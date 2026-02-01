#include "Evaluator.h"
#include "../core/Board.h"

using namespace chess;

Evaluator::Evaluator() {}

int Evaluator::evaluate(const Board &b) const {
    (void)b;
    // TODO: simple material + positional evaluation
    return 0;
}
