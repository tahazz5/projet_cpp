#include "Square.h"

Square::Square(int idx) : index(idx) {}
int Square::get_rank() const { return index/8; }
std::string Square::to_string() const {
    char file = 'a' + (index % 8);
    char rank = '1' + (index / 8);
    return std::string(1, file) + std::string(1, rank);
}
int Square::get_index() const {
    return index;
}