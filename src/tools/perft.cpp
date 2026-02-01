#include "../core/board.h"
#include "../movegen/move_generator.h"
#include <cstdint>
#include <iostream>

using namespace chess;

uint64_t perft_count(Board &b, int depth) {
    if (depth == 0) return 1;
    uint64_t nodes = 0;
    auto moves = MoveGenerator::generate_legal(b);
    for (const auto &m : moves) {
        MoveUndo u = b.make_move(m);
        nodes += perft_count(b, depth - 1);
        b.undo_move(u);
    }
    return nodes;
}

int main(int argc, char **argv) {
    Board b;
    int depth = 4;
    if (argc > 1) depth = std::stoi(argv[1]);
    uint64_t nodes = perft_count(b, depth);
    std::cout << "perft depth=" << depth << " nodes=" << nodes << std::endl;
    return 0;
}
