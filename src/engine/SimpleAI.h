#pragma once

#include "../core/Position.h"
#include "../core/Move.h"

class SimpleAI {
public:
    explicit SimpleAI(int depth = 2);
    Move chooseMove(Position &position);

private:
    int maxDepth;

    int evaluate(const Position &position) const;
    int minimax(Position &position, int depth, int alpha, int beta) const;
};
