#pragma once

#include "../core/Board.h"

namespace chess {

class UCIEngineAdapter {
public:
    UCIEngineAdapter(Board &b);
    void run();
private:
    Board &board;
};

} // namespace chess
