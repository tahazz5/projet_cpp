#include "uci.h"
#include "../core/board.h"
#include <iostream>
#include <sstream>

using namespace chess;

UCI::UCI(Board &b) : board(b) {}

void UCI::handle_position(const std::string &cmd) {
    if (cmd.find("startpos") != std::string::npos) {
        board.set_fen("");
    } else {
        auto pos = cmd.find("fen");
        if (pos != std::string::npos) {
            std::string fen = cmd.substr(pos + 4);
            board.set_fen(fen);
        }
    }
}

void UCI::handle_go(const std::string &cmd) {
    // Support minimal: "go perft depth X"
    if (cmd.find("perft") != std::string::npos) {
        std::istringstream iss(cmd);
        std::string token;
        int depth = 1;
        while (iss >> token) {
            if (token == "depth") iss >> depth;
        }
        extern uint64_t perft_count(chess::Board &b, int depth);
        uint64_t nodes = perft_count(board, depth);
        std::cout << "perft " << depth << " nodes " << nodes << std::endl;
    }
}

void UCI::loop() {
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "uci") {
            std::cout << "id name projet_cpp_engine\n";
            std::cout << "id author <you>\n";
            std::cout << "uciok\n";
        } else if (line == "isready") {
            std::cout << "readyok" << std::endl;
        } else if (line.rfind("position", 0) == 0) {
            handle_position(line);
        } else if (line.rfind("go", 0) == 0) {
            handle_go(line);
        } else if (line == "quit") {
            break;
        }
    }
}
