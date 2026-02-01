#pragma once

#include "../core/Board.h"

namespace chess {

class BoardRenderer {
public:
    static void render(const Board &b);
};

} // namespace chess
