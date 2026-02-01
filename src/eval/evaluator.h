#pragma once

namespace chess {

class Board;

class Evaluator {
public:
    Evaluator();
    int evaluate(const Board &b) const;
};

} // namespace chess
