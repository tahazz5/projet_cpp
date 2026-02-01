#pragma once

#include <string>

namespace chess {

class UCIProtocol {
public:
    static void process_command(const std::string &cmd);
};

} // namespace chess
