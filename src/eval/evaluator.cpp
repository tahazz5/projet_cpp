#include "evaluator.h"
#include "../core/board.h"

using namespace chess;

Evaluator::Evaluator() {}

int Evaluator::evaluate(const Board &b) const {
    (void)b;
    // TODO: matériel + piece-square tables + mobilité
    return 0;
}
