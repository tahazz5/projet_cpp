#pragma once
#include <vector>
#include "../core/Position.h"
#include "../core/Move.h"

class MoveGenerator {
public:
    static std::vector<Move> generateMoves(const Position& position);
};


