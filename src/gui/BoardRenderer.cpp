#include "BoardRenderer.h"
#include <iostream>

using namespace chess;

void BoardRenderer::render(const Board &b) {
    std::cout << "[BoardRenderer] rendering board to console..." << std::endl;
    b.print();
}
