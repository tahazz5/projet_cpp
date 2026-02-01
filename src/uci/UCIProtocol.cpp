#include "UCIProtocol.h"
#include <iostream>

using namespace chess;

void UCIProtocol::process_command(const std::string &cmd) {
    std::cout << "[UCI] received: " << cmd << std::endl;
    // TODO: parse basic UCI commands (position, go, isready, quit)
}
