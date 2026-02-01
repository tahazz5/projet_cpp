#include "UCIEngineAdapter.h"
#include "UCIProtocol.h"
#include <iostream>

using namespace chess;

UCIEngineAdapter::UCIEngineAdapter(Board &b) : board(b) {}

void UCIEngineAdapter::run() {
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "quit") break;
        UCIProtocol::process_command(line);
    }
}
