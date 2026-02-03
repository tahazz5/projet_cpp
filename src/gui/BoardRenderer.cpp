#include "BoardRenderer.h"
#include <iostream>

using namespace chess;

void BoardRenderer::render(const Board &b) {
    std::cout << b.toString() << std::endl;
}
